#pragma once

#include "File.h"
#include "RLE.h"
#include "Haffman.h"
#include "LZ77.h"
#include "pool.h"

#include <list>
#include <thread>
#include <mutex>


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
		ThreadPool threadPool(std::thread::hardware_concurrency());
		std::mutex compressedFilesMutex;

		for (auto it = files.begin(); it != files.end(); ++it){
			threadPool.add_task([&, it] {
				std::string lzCompressedData = LZ77::encode((*it).data);
				TBitField haffCompressedData = Haffman::encode(lzCompressedData);

				std::lock_guard<std::mutex> lg(compressedFilesMutex);
				compressedFiles.push_back(File<TBitField>(haffCompressedData, (*it).directory));
			});
		}

		threadPool.wait_all_tasks();

		files.clear();
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

