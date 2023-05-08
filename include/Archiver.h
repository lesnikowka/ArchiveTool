#pragma once

#include "File.h"
#include "RLE.h"
#include <list>

class Archiver {
public:
	Archiver() = default;

	Archiver(const Archiver& other) :
		files(other.files),
		compressedFiles(other.compressedFiles)
	{
	}

	Archiver(Archiver&& other):
		files(std::move(other.files)),
		compressedFiles(std::move(other.compressedFiles))
	{
	}

	Archiver& operator=(const Archiver& other) {
		files = other.files;
		compressedFiles = other.compressedFiles;

		return *this;
	}

	Archiver& operator=(Archiver&& other) {
		files = std::move(other.files);
		compressedFiles = std::move(other.compressedFiles);

		return *this;
	}
	
	void addFile(const std::string& directory) {
		files.push_back(loadFile(directory))
	}


	void compress() {
		RLE rle;

		for (const File& fl : files) {
			compressedFiles.push_back(File(rle.encode(fl.data), fl.directory));
		}
	}

	void save(const std::string& outputDir) {
		for (const File& fl: compressedFiles) {
			saveFile(fl, outputDir);
		}
	}

	void clear() {
		files.clear();
		compressedFiles.clear();
	}
private:
	std::list<File> files;
	std::list<File> compressedFiles;
};