#pragma once

#include "File.h"
#include "RLE.h"
#include <list>
#include "Haffman.h"

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
		files.push_back(loadFile(directory));
	}

	void compress() {
		Haffman h;
		for (File<std::string> f : files) {
			compressedFilesBinary.push_back(File<TBitField>(h.encode(f.data), f.directory));
		}
	}

	void save(const std::string& outputDir) {
		for (const File<std::string>& fl: compressedFiles) {
			saveFile(fl, outputDir);
		}
		for (const File<TBitField>& fl : compressedFilesBinary) {
			saveFile(fl, outputDir);
		}
	}

	void clear() {
		files.clear();
		compressedFiles.clear();
		compressedFilesBinary.clear();
	}
private:
	std::list<File<std::string>> files;
	std::list<File<std::string>> compressedFiles;
	std::list<File<TBitField>> compressedFilesBinary;
};