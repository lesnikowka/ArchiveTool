#pragma once

#include "File.h"
#include "RLE.h"
#include "Haffman.h"
#include "pool.h"

#include <list>
#include <Archiver.h>


std::string getExtension(const std::string& name) {
	int pos = name.rfind('.');
	if (pos == std::string::npos) {
		throw std::invalid_argument("Incorrect file name");
	}
	return name.substr(pos);
}

std::string delExtension(const std::string& name, const std::string& ex) {
	std::string extension = getExtension(name);

	if (extension != ex) {
		throw std::invalid_argument("Incorrect extension");
	}

	int pos = name.rfind('.');

	return name.substr(0, pos);
}


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
		files.push_back(loadBinaryFile(directory));
	}

	void unpack() {
		auto it = files.begin();
		while (it != files.end()) {
			std::string haffDecompressedData = Haffman::decode((*it).data);

			unpackedFiles.push_back(File<std::string>(LZ77::decode(haffDecompressedData), delExtension((*it).directory, ARCHIVE_EXTENSION)));
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
	std::list<File<TBitField>> files;
	std::list<File<std::string>> unpackedFiles;
};