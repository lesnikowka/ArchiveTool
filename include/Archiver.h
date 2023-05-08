#pragma once

#include "FileLoader.h"
#include "CompressedFile.h"
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
	
	void addFile(const std::string& directory, bool binaryMode = true) {
		files.push_back(std::move(FileLoader(directory, binaryMode)));
	}


	void compress() {
		RLE rle;

		for (const FileLoader& fl : files) {
			rle.processData(fl.getData());
			
			compressedFiles.push_back(std::move(CompressedFile(fl.getDirectory(),rle.getProcessedData())));
		}
	}

	void save(const std::string& outputDir, bool binaryMode = true) {
		for (const CompressedFile& fl: compressedFiles) {
			std::ofstream ofs(outputDir + fl.getName(), std::ios::binary);

			ofs << fl.getData();

			ofs.close();
		}
	}

	void clear() {
		files.clear();
		compressedFiles.clear();
	}
private:
	std::list<FileLoader> files;
	std::list<CompressedFile> compressedFiles;
};