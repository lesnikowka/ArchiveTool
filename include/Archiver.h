#include "FileLoader.h"
#include <list>

class Archiver {
public:
	
	void addFile(std::string& directory, bool binaryMode = true) {
		files.push_back(FileLoader(directory, binaryMode));
	}


	void compress() {

	}

	void save(const std::string& outputDirectory) {

	}

	void clear() {
		files.clear();
	}
private:
	std::list<FileLoader> files;
};