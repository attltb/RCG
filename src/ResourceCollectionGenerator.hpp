#ifndef _ResourceCollectionGeneratorHeader_
#define _ResourceCollectionGeneratorHeader_
#include <stddef.h>
#include <stdlib.h>
#include <string>
#include <vector>
#include "ResourceKind.hpp"
struct MemoryChunk {
	unsigned int size;
	void* addr;
	MemoryChunk() : size(0), addr(nullptr) {};
	MemoryChunk(unsigned int _size, void* _addr) : size(_size), addr(_addr) {}
};
class ResourceElement {
public:
	std::string name;
	ResourceKind kind;
	std::vector<MemoryChunk> chunks;

public:
	ResourceElement(std::string _name, ResourceKind _kind, const std::vector<MemoryChunk>& _chunks) : name(_name), kind(_kind), chunks(_chunks) {}

private:
	static size_t buff(size_t size_val) {
		if (size_val % 4) return size_val + 4 - (size_val % 4);
		return size_val;
	}

public:
	size_t size_header() const {
		size_t ret = 0;
		ret += (2 + chunks.size()) * sizeof(int);
		ret += (name.size() + 1) * sizeof(char);
		return buff(ret);
	}
	size_t size_data() const {
		size_t ret = 0;
		for (auto it = chunks.begin(); it != chunks.end(); it++) ret += buff(it->size);
		return ret;
	}
	void write(void* ptr, size_t& offset_header, size_t& offset_data) {
		int* pthis_header_info = (int*)((size_t)ptr + offset_header);
		pthis_header_info[0] = (int)kind;
		pthis_header_info[1] = (int)chunks.size();
		
		int* pthis_header_offsets = pthis_header_info + 2;
		for (unsigned int i = 0; i < chunks.size(); i++) {
			pthis_header_offsets[i] = (int)offset_data;
			memcpy((void*)((size_t)ptr + offset_data), chunks[i].addr, chunks[i].size);
			offset_data += buff(chunks[i].size);
		}
		char* pthis_name = (char*)(pthis_header_offsets + chunks.size());
		strcpy(pthis_name, name.c_str());
		offset_header += size_header();
	}
};
class ResourceCollectionGenerator {
	static const int magicNumber = 'rc';
	static const size_t size_magic = sizeof(int);
	size_t size_header;
	size_t size_data;
	std::vector<ResourceElement*> resourceElements;

public:
	void addResourceElement(std::string name, ResourceKind kind, const std::vector<MemoryChunk>& chunks) {
		ResourceElement* newElement = new ResourceElement(name, kind, chunks);
		size_header += newElement->size_header();
		size_data += newElement->size_data();
		resourceElements.push_back(newElement);
	}

public:
	size_t size_total() {
		return size_magic + size_header + size_data;
	}
	void* generate() {
		void* ptr = new char[size_total()];
		*((int*)ptr) = magicNumber;

		size_t offset_header = size_magic;
		size_t offset_data = size_magic + size_header;
		for (auto it = resourceElements.begin(); it != resourceElements.end(); it++) {
			(*it)->write(ptr, offset_header, offset_data);
		}
		return ptr;
	}

public:
	ResourceCollectionGenerator() : size_header(0), size_data(0) {}
	~ResourceCollectionGenerator() {
		for (unsigned int i = 0; i < resourceElements.size(); i++) {
			delete resourceElements[i];
		}
	}
};
#endif