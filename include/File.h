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

	File(const ContainerType& data_, std::string directory_) : data(data_), directory(directory_) {}

	File(ContainerType&& data_, std::string directory_) : data(data_), directory(directory_) {}
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
	
	char* buf;



	
}

std::string getName(std::string directory) {
	int leftBound = directory.rfind('/');

	if (leftBound == std::string::npos) {
		leftBound = 0;
	}
	else {
		leftBound++;
	}

	return directory.substr(leftBound);
}

void saveFile(const File<std::string>& fl, const std::string& outputDir) {
	std::ofstream ofs(outputDir + getName(fl.directory), ios::binary);
	if (ofs.is_open()) {
		ofs << fl.data;
	}
	else {
		throw std::invalid_argument("File was not opened");
	}

	ofs.close();
}

void saveFile(const File<TBitField> fl, const std::string& outputDir) {
	std::ofstream ofs(outputDir + getName(fl.directory), std::ios::binary);

	if (ofs.is_open()) {
		ofs.write((const char*)&(fl.data[0]), fl.data.GetCapacity());
	}
	else {
		throw std::invalid_argument("File was not opened");
	}

	ofs.close();
}