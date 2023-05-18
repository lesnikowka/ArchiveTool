#pragma once
#include <vector>
#include "HaffmanTreeCreator.h"
#include "tbitfield.h"

class Haffman {
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
		std::vector<int> freq = collectFrequency(data);
		std::vector<std::vector<bool>> codes = hc.createCodes(freq);

		size_t sizeOfCompressedData = 0;

		for (int i = 0; i < codes.size(); i++) {
			sizeOfCompressedData += codes[i].size() * freq[i];
		}

		TBitField CompressedData(sizeOfCompressedData);

		size_t i = 0;
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

	std::string decode(const std::string& data)  {
		return std::string();
	}
private:
	std::vector<int> collectFrequency(const std::string& data) {
		std::vector<int> frequency(256);

		for (unsigned char c : data) {
			frequency[(int)c]++;
		}

		return frequency;
	}

	std::vector<std::vector<bool>> createHaffmanCodes(const std::vector<int> frequency) {
		std::vector<std::vector<bool>> haffmanTable(256);

	}

};