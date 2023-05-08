#pragma once

#include <string>
#include <fstream>
#include <vector>
#include <sstream>
#include <iterator>

struct File {
	std::string data;

	std::string directory;
};

std::string loadData(const std::string& dir) {
	std::ifstream ifs;
	std::ostringstream os;

	std::string sourceData;

	
	ifs.open(dir, std::ios::binary);
	

	if (ifs.is_open() == false) {
		throw std::invalid_argument("File was not opened");
	}

	os << ifs.rdbuf();

	sourceData = std::move(os.str());

	return sourceData;
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

void saveFile(const File& fl, const std::string& outputDir) {

	std::ofstream ofs(outputDir + getName(fl.directory), std::ios::binary);

	ofs << fl.data;

	ofs.close();
}
