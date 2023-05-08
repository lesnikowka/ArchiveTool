#pragma once

#include <string>
#include <fstream>
#include <vector>
#include <sstream>
#include <iterator>

class FileLoader {
public:
	FileLoader() = default;

	FileLoader(const std::string& dir, bool binaryMode = true):
		directory(dir)
	{
		loadData(dir, binaryMode);
	}

	FileLoader(const FileLoader& other):
		sourceData(other.sourceData),
		directory(other.directory)
	{
	}
	
	FileLoader(FileLoader&& other):
		sourceData(std::move(other.sourceData)),
		directory(std::move(other.directory))
	{
	}

	FileLoader& operator=(const FileLoader& other) {
		sourceData = other.sourceData;
		directory = other.directory;

		return *this;
	}

	FileLoader& operator=(FileLoader&& other) {
		sourceData = std::move(other.sourceData);
		directory = std::move(other.directory);

		return *this;
	}

	const std::string& getData() const{
		return sourceData;
	}

	std::string getDirectory() const {
		return directory;
	}

	std::string getName() const {
		int leftBound = directory.rfind('/');

		if (leftBound == std::string::npos) {
			leftBound = 0;
		}
		else {
			leftBound++;
		}

		return directory.substr(leftBound);
	}

	void loadData(const std::string& dir, bool binaryMode = true) {
		std::ifstream ifs;
		std::ostringstream os;
		
		if (binaryMode == true) {
			ifs.open(dir, std::ios::binary);
		}
		else {
			ifs.open(dir);
		}
		
		if (ifs.is_open() == false) {
			throw std::invalid_argument("File was not opened");
		}
		
		os << ifs.rdbuf();

		sourceData = std::move(os.str());
		
	}

private:
	std::string sourceData;

	std::string directory;
};