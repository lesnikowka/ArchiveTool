#pragma once

#include <list>

#include "File.h"
#include "RLE.h"
#include "Haffman.h"
#include "Archiver.h"



class Unpacker {
public:
	Unpacker() = default;

	Unpacker(const Unpacker& other) :
		files(other.files),
		unpackedFiles(other.unpackedFiles)
	{
	}

	Unpacker(Unpacker&& other) noexcept :
		files(std::move(other.files)),
		unpackedFiles(std::move(other.unpackedFiles))
	{
	}

	Unpacker& operator=(const Unpacker& other) {
		files = other.files;
		unpackedFiles = other.unpackedFiles;

		return *this;
	}

	Unpacker& operator=(Unpacker&& other) noexcept {
		files = std::move(other.files);
		unpackedFiles = std::move(other.unpackedFiles);

		return *this;
	}

	void addFile(const std::string& directory) {
		files.push_back(loadFile(directory));
	}

	void unpack() {
		Haffman haff;
		LZ77 lz;
		
		auto it = files.begin();
		while (it != files.end()) {

			if (getExtension((*it).directory) == LZ_HAFF_EXTENSION) {
				std::string lzDecompressedData = lz.decode((*it).data);

				TBitField compressedDataForHaff = TBitField((unsigned char*)&lzDecompressedData[0], lzDecompressedData.size(), lzDecompressedData.size() * 8);

				unpackedFiles.push_back(File<std::string>(haff.decode(compressedDataForHaff), delExtension((*it).directory, LZ_HAFF_EXTENSION)));
			}
			else if(getExtension((*it).directory) == LZ_EXTENSION) {
				unpackedFiles.push_back(File<std::string>(lz.decode((*it).data), delExtension((*it).directory, LZ_EXTENSION)));
			}
		
			it = files.erase(it);
		}
	}

	void save(const std::string& outputDir) {
		for (const File<std::string>& fl : unpackedFiles) {
			saveFile(fl, outputDir);
		}
	}

	void clear() {
		files.clear();
		unpackedFiles.clear();
	}
private:
	std::list<File<std::string>> files;
	std::list<File<std::string>> unpackedFiles;
};