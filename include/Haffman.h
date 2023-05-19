#pragma once
#include <vector>
#include "HaffmanTreeCreator.h"
#include "tbitfield.h"

class Haffman {
	const size_t SIZE_OF_SERVICE_INFO = 2056;
public:
	Haffman() = default;

	void printCodes(std::vector<std::vector<bool>> v) {
		for (int i = 0; i < v.size(); i++) {
			if (v[i].size()) {
				std::cout << (char)i << ": ";
				for (auto e : v[i]) {
					std::cout << e;
				}
				std::cout << std::endl;
			}
		}
	}

	TBitField encode(const std::string& data)  {
		HaffmanTreeCreator hc;
		std::vector<size_t> freq = collectFrequency(data);
		std::vector<std::vector<bool>> codes = hc.createCodes(freq);

		size_t sizeOfCompressedData = getSizeOfCompressedData(codes, freq);

		TBitField CompressedData(sizeOfCompressedData + SIZE_OF_SERVICE_INFO);

		writeNumberInBitField(CompressedData, sizeOfCompressedData, 0);

		for (size_t i = 0; i < freq.size(); i++){
			writeNumberInBitField(CompressedData, freq[i], sizeof(size_t) * 8 * (1 + i));
		}

		size_t i = SIZE_OF_SERVICE_INFO;
		for (unsigned char c : data) {
			size_t j = 0;
			for (; j < codes[c].size(); j++) {
				if (codes[c][j]) {
					CompressedData.SetBit(i + j);
				}
			}
			i += j;
		}

		return CompressedData;
	}

	std::string decode(TBitField)  {
		std::string;
	}
private:
	std::vector<size_t> collectFrequency(const std::string& data) {
		std::vector<size_t> frequency(256);

		for (unsigned char c : data) {
			frequency[(size_t)c]++;
		}

		return frequency;
	}

	std::vector<std::vector<bool>> createHaffmanCodes(const std::vector<size_t> frequency) {
		std::vector<std::vector<bool>> haffmanTable(256);

	}

	size_t getSizeOfCompressedData(const std::vector<std::vector<bool>>& codes, const std::vector<size_t>& freq) {
		size_t sizeOfCompressedData = 0;

		for (int i = 0; i < codes.size(); i++) {
			sizeOfCompressedData += codes[i].size() * freq[i];
		}

		return sizeOfCompressedData;
	}

	template<class T>
	void writeNumberInBitField(TBitField& tf, const T& val, size_t start) {
		size_t bitsize = sizeof(T) * 8;

		for (int i = bitsize-1; i >= 0; i--) {
			if ((val << bitsize - i - 1)>> bitsize - 1){
				tf.SetBit(start + bitsize - i - 1);
			}
		}
	}
};