#include "FileLoader.h"
#include "CompressedFile.h"
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
	
	void addFile(std::string& directory, bool binaryMode = true) {
		files.push_back(FileLoader(directory, binaryMode));
	}


	void compress() {

	}

	void clear() {
		files.clear();
		compressedFiles.clear();
	}
private:
	std::list<FileLoader> files;
	std::list<CompressedFile> compressedFiles;
};