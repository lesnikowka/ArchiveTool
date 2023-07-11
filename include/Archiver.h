#pragma once

#include "File.h"
#include "RLE.h"
#include <list>
#include "Haffman.h"
#include "lz77.h"


const std::string LZ_EXTENSION = ".lz";
const std::string LZ_HAFF_EXTENSION = ".lzhf";


class Archiver {
	enum class ALGORITHM {
		HAFFMAN,
		LZ77,
		HAFFMAN_LZ77
	};

public:
	Archiver() = default;

	Archiver(const Archiver& other) :
		files(other.files),
		compressedFiles(other.compressedFiles)
	{
	}

	Archiver(Archiver&& other) noexcept :
		files(std::move(other.files)),
		compressedFiles(std::move(other.compressedFiles))
	{
	}

	Archiver& operator=(const Archiver& other) {
		files = other.files;
		compressedFiles = other.compressedFiles;

		return *this;
	}

	Archiver& operator=(Archiver&& other) noexcept {
		files = std::move(other.files);
		compressedFiles = std::move(other.compressedFiles);

		return *this;
	}

	void addFile(const std::string& directory) {
		files.push_back(loadFile(directory));
	}

	void compress() {
		LZ77 lz;
		Haffman haff;

		auto it = files.begin();

		while (it != files.end()) {
			TBitField haffCompressedData = haff.encode((*it).data);

			if (haffCompressedData.GetCapacity() < (*it).data.size()) {

				std::string compressedDataForLZ((char*)(&(haffCompressedData[0])), haffCompressedData.GetCapacity());

				compressedFiles.push_back(File<std::string>(lz.encode(compressedDataForLZ), (*it).directory));
				extensions.push_back(ALGORITHM::HAFFMAN_LZ77);
			}
			else {
				compressedFiles.push_back(File<std::string>(lz.encode((*it).data), (*it).directory));
				extensions.push_back(ALGORITHM::LZ77);
			}

			it = files.erase(it);
		}

	}

	void save(const std::string& outputDir) {

		size_t i = 0;
		for (const File<std::string>& fl : compressedFiles) {
			std::string extension;

			if (extensions[i] == ALGORITHM::HAFFMAN_LZ77) {
				extension = LZ_HAFF_EXTENSION;
			}
			else if (extensions[i] == ALGORITHM::LZ77) {
				extension = LZ_EXTENSION;
			}

			saveFile(fl, outputDir, extension);

			i++;
		}

		clear();
	}

	void clear() {
		files.clear();
		compressedFiles.clear();
		extensions.clear();
	}
private:
	std::list<File<std::string>> files;
	std::list<File<std::string>> compressedFiles;
	std::vector<ALGORITHM> extensions;
};