#include <string>
#include <fstream>
#include <vector>

class File {
public:
	File() = default;

	File(const std::string& dir, bool binaryMode = true):
		directory(dir)
	{
		loadData(dir, binaryMode);
	}

	File(const File& other):
		sourceData(other.sourceData),
		directory(other.directory)
	{
	}
	
	File(File&& other):
		sourceData(std::move(other.sourceData)),
		directory(std::move(other.directory))
	{
	}

	File& operator=(const File& other) {
		sourceData = other.sourceData;
		directory = other.directory;

		return *this;
	}

	File& operator=(File&& other) {
		sourceData = std::move(other.sourceData);
		directory = std::move(other.directory);

		return *this;
	}

	std::string getData() {
		return sourceData;
	}

	std::string getDirectory() {
		return directory;
	}

	void loadData(const std::string& dir, bool binaryMode = true) {
		std::ifstream ifs(dir);

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

		delete[] buff;

		sourceData = std::move(std::string(buff));
	}

private:
	std::string sourceData;

	std::string directory;
};