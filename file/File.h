#pragma once

#include <string>
#include <fstream>
#include <vector>
#include <sstream>
#include <iterator>
#include "tbitfield.h"

template <class ContainerType>
struct File {
	ContainerType data;
	std::string directory;

	File() = default;

	File(const ContainerType& data_, std::string directory_) : 
		data(data_), 
		directory(directory_) {}

	File(ContainerType&& data_, std::string directory_) : 
		data(data_), 
		directory(directory_) {}

	File(const File& file) : 
		data(file.data),
		directory(file.directory) {}
		 
	File& operator=(const File& file) {
		data = file.data;
		directory = file.directory;

		return *this;
	}

	File& operator=(File&& file) {
		data = std::move(file.data);
		directory = std::move(file.directory);

		return *this;
	}

};

std::string loadData(const std::string& dir) {
	std::ifstream ifs;
	std::ostringstream os;
	std::string sourceData;

	ifs.open(dir, std::ios::binary);
	
	if (ifs.is_open()) {
		os << ifs.rdbuf();

		sourceData = std::move(os.str());
	}
	else {
		throw std::invalid_argument("File was not opened");
	}

	return sourceData;
}

File<std::string> loadFile(const std::string& dir) {
	File<std::string> file(loadData(dir), dir);

	return file;
}

File<TBitField> loadBinaryFile(const std::string& dir) {
	char* buf =  nullptr;
	long long size = 0;
	std::ifstream ifs(dir, std::ios::binary);
	
	if (ifs.is_open()) {

		ifs.seekg(0, std::ios::end);

		size = ifs.tellg();

		ifs.seekg(0, std::ios::beg);
		buf = new char[size];

		ifs.read(buf, size);
		ifs.close();
	}
	else {
		throw std::invalid_argument("File was not opened");
	}
	
	return File<TBitField>(TBitField((unsigned char*)buf, size, size * 8), dir);
}

std::string getName(std::string directory) {
	int leftBound = std::max((int)directory.rfind('/'), (int)directory.rfind('\\'));

	leftBound++;

	return directory.substr(leftBound);
}

void saveFile(const File<std::string>& fl, const std::string& outputDir, const std::string& extension = "") {
	std::ofstream ofs(outputDir + getName(fl.directory) + extension, ios::binary);


	if (ofs.is_open()) {
		ofs << fl.data;
	}
	else {
		throw std::invalid_argument("File was not opened");
	}

	ofs.close();
}

void saveFile(const File<TBitField> fl, const std::string& outputDir, const std::string& extension = "") {
	std::ofstream ofs(outputDir + getName(fl.directory) + extension, std::ios::binary);

	if (ofs.is_open()) {
		ofs.write((const char*)&(fl.data[0]), fl.data.GetCapacity());
	}
	else {
		throw std::invalid_argument("File was not opened");
	}

	ofs.close();
}