#include <string>

class RLEencoder {
public:
	std::string encode(const std::string& data) {
		std::string encodedData;

		std::pair<bool, unsigned> info;


		for (unsigned i = 0; i < data.size(); i++) {
			info = getLenghtAndIsSimilar(data[i]);

			if (!info.first) std::cout << "something";

			if (info.first) {
				addSimilarSequence(encodedData, data[i + 1], info.second);
				i++;
			}
			else {
				encodedData += data.substr(i+1, info.second - 1);
				i += info.second;
			}
		}
		return encodedData;
	}


private:
	std::pair<bool, unsigned> getLenghtAndIsSimilar(unsigned char c) {
		return std::make_pair((c << 7), (c >> 1));
	}

	void addSimilarSequence(std::string& s, char c, unsigned n) {
		for (unsigned i = 0; i < n; i++) {
			s += c;
		}
	}

};