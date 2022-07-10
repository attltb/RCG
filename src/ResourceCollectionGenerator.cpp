#include <fstream>
#include <iostream>
#include <string>
#include <opencv2/core.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/imgcodecs.hpp>
#include "ErrorStrings.hpp"
#include "ResourceCollectionGenerator.hpp"
#include "Parser.hpp"
using namespace std;
using namespace cv;
struct Color32 {
	uint8_t blue;
	uint8_t green;
	uint8_t red;
	uint8_t alpha;
};

Mat LoadAs8UC4(const char* path) {
	Mat input = imread(path, IMREAD_UNCHANGED);
	if (input.empty()) return input;

	Mat output;
	switch (input.type()) {
	case CV_8UC1:
	case CV_8UC2:
	case CV_8UC3:
	case CV_8UC4:
		output = input;
		break;
	case CV_8SC1:
	case CV_8SC2:
	case CV_8SC3:
	case CV_8SC4:
		input.convertTo(output, CV_8U, 1.0, 128);
		break;
	case CV_16UC1:
	case CV_16UC2:
	case CV_16UC3:
	case CV_16UC4:
		input.convertTo(output, CV_8U, 255.0 / 65535.0);
		break;
	case CV_16SC1:
	case CV_16SC2:
	case CV_16SC3:
	case CV_16SC4:
		input.convertTo(output, CV_8U, 255.0 / 65535.0, 32768.0);
		break;
	case CV_16FC1:
	case CV_16FC2:
	case CV_16FC3:
	case CV_16FC4:
		input.convertTo(output, CV_8U, 255.0);
		break;
	case CV_32FC1:
	case CV_32FC2:
	case CV_32FC3:
	case CV_32FC4:
		input.convertTo(output, CV_8U, 255.0);
		break;
	case CV_64FC1:
	case CV_64FC2:
	case CV_64FC3:
	case CV_64FC4:
		input.convertTo(output, CV_8U, 255.0);
		break;
	}
	switch (output.channels()) {
	case 1:
		cvtColor(output, output, COLOR_GRAY2BGRA);
		break;
	case 3:
		cvtColor(output, output, COLOR_BGR2BGRA);
		break;
	}
	return output;
}
MemoryChunk GetBinary(const char* path, const char* path_abs) {
	FILE* file = fopen(path, "rb");
	if (!file) file = fopen(path_abs, "rb");
	if (!file) {
		cout << getErrorString_File_CannotOpen(path) << endl;
		return MemoryChunk();
	}

	fseek(file, 0, SEEK_END);
	int size = ftell(file);
	int size_chunk = sizeof(int) + size;
	char* addr = new char[size_chunk];

	fseek(file, 0, SEEK_SET);
	((int*)addr)[0] = size;
	if (fread(addr + sizeof(int), 1, size, file) != size) {
		cout << getErrorString_File_Unknown(path) << endl;
		delete[] addr;
		fclose(file);
		return MemoryChunk();
	}
	fclose(file);
	return MemoryChunk(size_chunk, addr);
}
MemoryChunk GetBitmap32(const char* path, const char* path_abs) {
	Mat image = LoadAs8UC4(path);
	if (image.empty()) LoadAs8UC4(path_abs);
	if (image.empty()) {
		cout << getErrorString_File_CannotOpenImage(path) << endl;
		return MemoryChunk();
	}

	Size sizer = image.size();
	int width = sizer.width;
	int height = sizer.height;
	int size = width * height;
	int size_chunk = 2 * sizeof(int) + size * sizeof(Color32);

	char* addr = new char[size_chunk];
	((int*)addr)[0] = width;
	((int*)addr)[1] = height;
	memcpy(addr + 2 * sizeof(int), image.ptr<Color32>(), size * sizeof(Color32));
	return MemoryChunk(size_chunk, addr);
}

bool GetData(ResourceCollectionGenerator& generator, string line, const char* path_folder) {
	Syntax_AddResourseElement parsed = parse(line);
	vector<MemoryChunk> chunks;
	switch (parsed.dataKind) {
	case ResourceKind::Binary:
		for (unsigned int i = 0; i < parsed.paths.size(); i++) {
			const string path_abs = parsed.paths[i] + string(path_folder);
			MemoryChunk chunk = GetBinary(parsed.paths[i].c_str(), path_abs.c_str());
			if (!chunk.size) return false;
			chunks.push_back(chunk);
		}
		break;
	case ResourceKind::Bitmap32:
		for (unsigned int i = 0; i < parsed.paths.size(); i++) {
			const string path_abs = parsed.paths[i] + string(path_folder);
			MemoryChunk chunk = GetBitmap32(parsed.paths[i].c_str(), path_abs.c_str());
			if (!chunk.size) return false;
			chunks.push_back(chunk);
		}
		break;
	}
	generator.addResourceElement(parsed.name, parsed.dataKind, chunks);
	return true;
}
bool GenerateOutput(const char* filename_o, ResourceCollectionGenerator& generator) {
	void* ptr = generator.generate();

	FILE* file = fopen(filename_o, "wb");
	if (!file) {
		cout << getErrorString_File_CannotCreate(filename_o) << endl;
		delete[] ptr;
		return false;
	}

	size_t wcount = fwrite(ptr, 1, generator.size_total(), file);
	fclose(file);
	delete[] ptr;
	return true;
}

string GetOutPath(string path_in) {
	size_t pos = path_in.rfind(".");
	if (pos != string::npos) path_in.replace(pos, string::npos, ".dat");
	return path_in;
}
string GetFolderPath(string path_in) {
	size_t pos_1 = path_in.rfind("/");
	size_t pos_2 = path_in.rfind("\\");
	size_t pos = (pos_1 == string::npos || (pos_2 != string::npos && pos_1 < pos_2)) ? pos_2 : pos_1;
	if (pos != string::npos) return path_in.erase(pos + 1, string::npos);
	else return "";
}
bool convert(string path_in, string path_out) {
	ResourceCollectionGenerator generator;
	ifstream f;

	const string path_folder = GetFolderPath(path_in);
	f.open(path_in, ios_base::beg);
	for (string line; getline(f, line);) {
		if (line.empty()) continue;
		for (; line.back() == '\\';) {
			line.pop_back();

			string addline;
			getline(f, addline);
			line += addline;
		}
		GetData(generator, line, path_folder.c_str());
	}
	f.close();

	return GenerateOutput(path_out.c_str(), generator);
}
bool convert(string path_in) {
	return convert(path_in, GetOutPath(path_in));
}

int main(int argc, char* argv[]) {
	if (argc == 1) return 0;
	else if (argc == 2) convert(argv[1]);
	else convert(argv[1], argv[2]);
	return 0;
};