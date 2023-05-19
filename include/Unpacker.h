#pragma once

#include "File.h"
#include "RLE.h"
#include <list>
#include "Haffman.h"

template <class CompressingStrategy>
class Unpacker {
};

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

template<>
class Unpacker<RLE> {
	const std::string ARCHIVE_EXTENSION = ".rle";
public:
	Unpacker() = default;

	Unpacker(const Unpacker& other) :
		files(other.files),
		unpackedFiles(other.unpackedFiles)
	{
	}

	Unpacker(Unpacker&& other) :
		files(std::move(other.files)),
		unpackedFiles(std::move(other.unpackedFiles))
	{
	}

	Unpacker& operator=(const Unpacker& other) {
		files = other.files;
		unpackedFiles = other.unpackedFiles;

		return *this;
	}

	Unpacker& operator=(Unpacker&& other) {
		files = std::move(other.files);
		unpackedFiles = std::move(other.unpackedFiles);

		return *this;
	}

	void addFile(const std::string& directory) {
		files.push_back(loadFile(directory));
	}

	void unpack() {
		RLE rle;

		auto it = files.begin();
		while (it != files.end()) {
			unpackedFiles.push_back(File<std::string>(rle.decode((*it).data), delExtension((*it).directory, ARCHIVE_EXTENSION)));
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




template<>
class Unpacker<Haffman> {
	const std::string ARCHIVE_EXTENSION = ".haff";
public:
	Unpacker() = default;

	Unpacker(const Unpacker& other) :
		files(other.files),
		unpackedFiles(other.unpackedFiles)
	{
	}

	Unpacker(Unpacker&& other) :
		files(std::move(other.files)),
		unpackedFiles(std::move(other.unpackedFiles))
	{
	}

	Unpacker& operator=(const Unpacker& other) {
		files = other.files;
		unpackedFiles = other.unpackedFiles;

		return *this;
	}

	Unpacker& operator=(Unpacker&& other) {
		files = std::move(other.files);
		unpackedFiles = std::move(other.unpackedFiles);

		return *this;
	}

	void addFile(const std::string& directory) {
		files.push_back(loadBinaryFile(directory));
	}

	void unpack() {
		Haffman h;

		auto it = files.begin();
		while (it != files.end()) {
			unpackedFiles.push_back(File<std::string>(h.decode((*it).data), delExtension((*it).directory, ARCHIVE_EXTENSION)));
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
