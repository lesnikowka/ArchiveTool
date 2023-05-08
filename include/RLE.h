#pragma once

#include <string>
#include <cassert>

class RLE {
public:
	RLE() = default;
	
	void processData(const std::string& data) {
		std::string result;
		
		if (data.size() > 3) {
		
			bool similar = data[0] == data[1];
		
			unsigned start = 0;
		
			for (unsigned i = 0; i < data.size() - 1; i++) {
				if (i - start > 126) {
        result += getSignByte(similar, i - start);
					if (similar) {
						result += data[i - 1];
					}
					else {
						result += data.substr(start, i - start - 1);
					}
					start = i;
				}
				if (data[i] == data[i + 1] && similar == false) {
					result += getSignByte(false, i - start);
					result += data.substr(start, i - start - 1);
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
			result += data.substr(start, data.size() - start - 1);			
		}
		
		processedData = std::move(result);
	}

	const std::string& getProcessedData() {
		return processedData;
	}
private:
	std::string processedData;

	unsigned char getSignByte(bool isSimilarSequence, unsigned lenght) {
		assert(lenght <= 127);

		unsigned char result = isSimilarSequence;

		result += (lenght << 1);

		return result;
	}
};