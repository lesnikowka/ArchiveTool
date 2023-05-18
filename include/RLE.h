#pragma once

#include <string>
#include <cassert>


class RLE {
public:
	RLE() = default;
	
	std::string encode(const std::string& data) {
		
		
		std::string result;
		
		
		if (data.size() > 3) {
		
			bool similar = data[0] == data[1];
		
			int start = 0;
		
			for (int i = 0; i < data.size() - 1; i++) {
				if (i - start > MAX_LENGHT) {
					result += getSignByte(similar, i - start);
					if (similar) {
						result += data[i - 1];
					}
					else {
						result += data.substr(start, i - start);
					}
					start = i;
				}
				if (data[i] == data[i + 1] && similar == false) {
					result += getSignByte(false, i - start);
					result += data.substr(start, i - start);
					start = i;
					similar = true;
				}
				else if (data[i] != data[i + 1] && similar == true) {
					result += getSignByte(true, i - start + 1);
					result += data[i];
					start = i + 1;
					similar = false;
				}
			}
		
			result += getSignByte(similar, data.size() - start);
			if (similar) {
				result += data[start];
			}
			else {
				result += data.substr(start, data.size() - start);
			}
		}
		
		return result;
	}

	std::string decode(const std::string& data)  {
		std::string encodedData;

		std::pair<bool, unsigned> info;


		for (unsigned i = 0; i < data.size(); i++) {
			info = getLenghtAndIsSimilar(data[i]);

			if (info.first) {
				addSimilarSequence(encodedData, data[i + 1], info.second);
				i++;
			}
			else {
				encodedData += data.substr(i + 1, info.second);
				i += info.second;
			}
		}
		return encodedData;
	}

private:
	const unsigned MAX_LENGHT = 126;

	unsigned char getSignByte(bool isSimilarSequence, int lenght) {
		assert(lenght <= 127 && lenght >=0);
		
		unsigned char result = isSimilarSequence;
		result += (lenght << 1);

		return result;
	}

	std::pair<bool, unsigned> getLenghtAndIsSimilar(unsigned char c) {
		unsigned char s = c << 7;

		return std::make_pair(s, (c >> 1));
	}

	void addSimilarSequence(std::string& s, unsigned char c, unsigned n) {
		for (unsigned i = 0; i < n; i++) {
			s += c;
		}
	}
};