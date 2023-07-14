#pragma once

#include "File.h"
#include "RLE.h"
#include <list>
#include "Haffman.h"
#include "LZ77.h"


const std::string ARCHIVE_EXTENSION = ".ajr";


class Archiver {
public:
	Archiver() = default;

	Archiver(const Archiver & other) :
		files(other.files),
		compressedFiles(other.compressedFiles)
	{
	}

	Archiver(Archiver && other) noexcept :
		files(std::move(other.files)),
		compressedFiles(std::move(other.compressedFiles))
	{
	}

	Archiver& operator=(const Archiver & other) {
		files = other.files;
		compressedFiles = other.compressedFiles;

		return *this;
	}

	Archiver& operator=(Archiver && other) noexcept {
		files = std::move(other.files);
		compressedFiles = std::move(other.compressedFiles);

		return *this;
	}

	void addFile(const std::string & directory) {
		files.push_back(loadFile(directory));
	}

	void compress() {
		LZ77 lz;
		Haffman haff;

		auto it = files.begin();

		while (it != files.end()) {
			std::string lzCompressedData = lz.encode((*it).data);

			compressedFiles.push_back(File<TBitField>(haff.encode(lzCompressedData), (*it).directory));

			it = files.erase(it);
		}

	}

	void save(const std::string & outputDir) {
		for (const File<TBitField>& fl: compressedFiles) {
			saveFile(fl, outputDir, ARCHIVE_EXTENSION);
		}
	}

	void clear() {
		files.clear();
		compressedFiles.clear();
	}
private:
	std::list<File<std::string>> files;
	std::list<File<TBitField>> compressedFiles;
};

