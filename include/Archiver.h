#pragma once

#include "File.h"
#include "RLE.h"
#include <list>
#include "Haffman.h"
#include "lz77.h"


const std::string HAFFMAN_ARCHIVE_EXTENSION = ".haff";
const std::string RLE_ARCHIVE_EXTENSION = ".rle";
const std::string LZ77_ARCHIVE_EXTENSION = ".lz77";



template <class CompressingStrategy>
class Archiver {
};


template<>
class Archiver<RLE> {
public:
	Archiver() = default;

	Archiver(const Archiver & other) :
		files(other.files),
		compressedFiles(other.compressedFiles)
	{
	}

	Archiver(Archiver && other) :
		files(std::move(other.files)),
		compressedFiles(std::move(other.compressedFiles))
	{
	}

	Archiver& operator=(const Archiver & other) {
		files = other.files;
		compressedFiles = other.compressedFiles;

		return *this;
	}

	Archiver& operator=(Archiver && other) {
		files = std::move(other.files);
		compressedFiles = std::move(other.compressedFiles);

		return *this;
	}

	void addFile(const std::string & directory) {
		files.push_back(loadFile(directory));
	}

	void compress() {
		RLE rle;

		auto it = files.begin();
		while (it != files.end()) {
			compressedFiles.push_back(File<std::string>(rle.encode((*it).data), (*it).directory));
			it = files.erase(it);
		}

	}

	void save(const std::string & outputDir) {
		for (const File<std::string>& fl: compressedFiles) {
			saveFile(fl, outputDir, RLE_ARCHIVE_EXTENSION);
		}
	}

	void clear() {
		files.clear();
		compressedFiles.clear();
	}
private:
	std::list<File<std::string>> files;
	std::list<File<std::string>> compressedFiles;
};


template<>
class Archiver<LZ77> {
public:
	Archiver() = default;

	Archiver(const Archiver& other) :
		files(other.files),
		compressedFiles(other.compressedFiles)
	{
	}

	Archiver(Archiver&& other) :
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
		LZ77 lz77;

		auto it = files.begin();
		while (it != files.end()) {
			compressedFiles.push_back(File<std::string>(lz77.encode((*it).data), (*it).directory));
			it = files.erase(it);
		}

	}

	void save(const std::string& outputDir) {
		for (const File<std::string>& fl : compressedFiles) {
			saveFile(fl, outputDir, LZ77_ARCHIVE_EXTENSION);
		}
	}

	void clear() {
		files.clear();
		compressedFiles.clear();
	}
private:
	std::list<File<std::string>> files;
	std::list<File<std::string>> compressedFiles;
};


template<>
class Archiver<Haffman> {
public:
	Archiver() = default;

	Archiver(const Archiver& other) :
		files(other.files),
		compressedFiles(other.compressedFiles)
	{
	}

	Archiver(Archiver&& other) :
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

		auto it = files.begin();
		while (it != files.end()) {
			compressedFiles.push_back(File<TBitField>(h.encode((*it).data), (*it).directory));
			it = files.erase(it);
		}

	}

	void save(const std::string& outputDir) {
		for (const File<TBitField>& fl : compressedFiles) {
			saveFile(fl, outputDir, HAFFMAN_ARCHIVE_EXTENSION);
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
