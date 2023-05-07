#include <string>
#include <fstream>
#include <vector>

class FileLoader {
public:
	FileLoader() = default;

	FileLoader(const std::string& dir, bool binaryMode = true):
		directory(dir)
	{
		loadData(dir, binaryMode);
	}

	FileLoader(const FileLoader& other):
		sourceData(other.sourceData),
		directory(other.directory)
	{
	}
	
	FileLoader(FileLoader&& other):
		sourceData(std::move(other.sourceData)),
		directory(std::move(other.directory))
	{
	}

	FileLoader& operator=(const FileLoader& other) {
		sourceData = other.sourceData;
		directory = other.directory;

		return *this;
	}

	FileLoader& operator=(FileLoader&& other) {
		sourceData = std::move(other.sourceData);
		directory = std::move(other.directory);

		return *this;
	}

	const std::string& getData() const{
		return sourceData;
	}

	std::string getDirectory() const {
		return directory;
	}

	void loadData(const std::string& dir, bool binaryMode = true) {
		std::ifstream ifs;

		if (binaryMode == true) {
			ifs.open(dir, std::ios::binary);
		}
		else {
			ifs.open(dir);
		}

		if (ifs.is_open() == false) {
			throw std::invalid_argument("File was not opened");
		}

		ifs.seekg(0, std::ios::end);
		std::streampos lenght = ifs.tellg();
		ifs.seekg(0, std::ios::beg);

		char* buff = new char[lenght];

		ifs.read(buff, lenght);
		ifs.close();

		std::string data(buff);

		sourceData = std::move(std::string(buff));

		delete[] buff;
	}

private:
	std::string sourceData;

	std::string directory;
};