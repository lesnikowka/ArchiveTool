#include <string>
#include <fstream>
#include <vector>

class FileData {
public:
	FileData() = delete;

	FileData(const std::string& dir, bool binaryMode = true) {
		sourceData = std::move(loadData(dir, binaryMode));
	}

	FileData(const FileData& other) {
		sourceData = other.sourceData;
	}

	FileData(FileData&& other) {
		sourceData = std::move(other.sourceData);
	}

	FileData& operator=(const FileData& other) {
		sourceData = other.sourceData;
	}

	FileData& operator=(FileData&& other) {
		sourceData = std::move(other.sourceData);
	}

	std::string getData() {
		return sourceData;
	}

private:
	std::string sourceData;

	std::string loadData(const std::string& dir, bool binaryMode = true) {
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

		return data;
	}
};