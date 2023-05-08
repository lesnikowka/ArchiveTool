#pragma once

#include "tbitfield.h"
#include <string>

class CompressedFile {
public:
	CompressedFile() = default;

	CompressedFile(const std::string& dir, const std::string& compressedData_) :
		directory(dir),
		compressedData(compressedData_)
	{
	}

	CompressedFile(const std::string& dir, std::string&& compressedData_) :
		directory(dir),
		compressedData(compressedData_)
	{
	}

	CompressedFile(const CompressedFile& other) :
		compressedData(other.compressedData),
		directory(other.directory)
	{
	}

	CompressedFile(CompressedFile&& other) :
		compressedData(std::move(other.compressedData)),
		directory(std::move(other.directory))
	{
	}

	CompressedFile& operator=(const CompressedFile& other) {
		compressedData = other.compressedData;
		directory = other.directory;

		return *this;
	}

	CompressedFile& operator=(CompressedFile&& other) {
		compressedData = std::move(other.compressedData);
		directory = std::move(other.directory);

		return *this;
	}

	const std::string& getData() const {
		return compressedData;
	}

	void setCompressedFile(const std::string& dir, const std::string& compressedData_) {
		compressedData = compressedData_;
		directory = dir;
	}

	void setCompressedFile(const std::string& dir, std::string&& compressedData_) {
		compressedData = compressedData_;
		directory = dir;
	}

	std::string getDirectory() const{
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
private:
	std::string compressedData;

	std::string directory;
};