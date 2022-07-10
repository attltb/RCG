#include "ErrorStrings.hpp"
std::string getErrorString_UnexpectedToken(std::string token) {
	return "에러 : 예기치 않은 토큰 \"" + token + "\" 입니다.\n";
}
std::string getErrorString_UnexpectedToken_ExpectedIdentifier(std::string token) {
	return "에러 : 예기치 않은 토큰 \"" + token + "\" 입니다. 식별자가 필요합니다.\n";
}
std::string getErrorString_UnexpectedToken_ExpectedFilePath(std::string token) {
	return "에러 : 예기치 않은 토큰 \"" + token + "\" 입니다. 파일 경로가 필요합니다.\n";
}
std::string getErrorString_UnexpectedToken_ExpectedFormat(std::string token) {
	return "에러 : 예기치 않은 토큰 \"" + token + "\" 입니다. 리소스 형식이 필요합니다.\n";
}
std::string getErrorString_UnexpectedToken_Expected(std::string token, std::string tokenExpected) {
	return "에러 : 예기치 않은 토큰 \"" + token + "\" 입니다. \"" + tokenExpected + "\"가 필요합니다.\n";
}
std::string getErrorString_UnexpectedLineBreak_ExpectedIdentifier() {
	return "에러 : 예기치 않은 줄 바꿈입니다. 식별자가 필요합니다.\n";
}
std::string getErrorString_UnexpectedLineBreak_ExpectedFilePath() {
	return "에러 : 예기치 않은 줄 바꿈입니다. 파일 경로가 필요합니다.\n";
}
std::string getErrorString_UnexpectedLineBreak_ExpectedFormat() {
	return "에러 : 예기치 않은 줄 바꿈입니다. 리소스 형식이 필요합니다.\n";
}
std::string getErrorString_UnexpectedLineBreak_Expected(std::string tokenExpected) {
	return "에러 : 예기치 않은 줄 바꿈입니다. 필요한 토큰은 \"" + tokenExpected + "\"입니다.\n";
}
std::string getErrorString_CannotParseALine(std::string line) {
	return "에러 : 줄 \"" + line + "\"를 파싱할 수 없습니다.\n";
}

std::string getErrorString_File_CannotOpen(std::string fileName) {
	return "파일 \"" + fileName + "\"를 열 수 없습니다.\n";
}
std::string getErrorString_File_CannotOpenImage(std::string fileName) {
	return "파일 \"" + fileName + "\"가 없거나 이미지 파일이 아닙니다.\n";
}
std::string getErrorString_File_CannotCreate(std::string fileName) {
	return "파일 \"" + fileName + "\"를 읽는 도중 알 수 없는 오류가 발생했습니다.\n";
}
std::string getErrorString_File_Unknown(std::string fileName) {
	return "파일 \"" + fileName + "\"를 생성할 수 없습니다.\n";
}