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

	std::string encode(const std::string& data)  {
		HaffmanTreeCreator hc;
		std::vector<int> freq = collectFrequency(data);
		std::vector<std::vector<bool>> codes = hc.createCodes(freq);
		//printCodes(codes);

		size_t sizeOfCompressedData = 0;

		for (int i = 0; i < codes.size(); i++) {
			sizeOfCompressedData += codes[i].size() * freq[i];
		}

		//std::vector<bool> compressedData(sizeOfCompressedData);
		TBitField tf(sizeOfCompressedData);

		size_t i = 0;
		for (unsigned char c : data) {
			size_t j = 0;
			for (; j < codes[c].size(); j++) {
				//compressedData[i + j] = codes[c][j];
				if (codes[c][j]) {
					tf.SetBit(i + j);
				}
			}
			i += j;
		}

		std::string result;
		//if (compressedData.size() % 8 == 0) {
		if (tf.GetLength() % 8 == 0){
			//result.resize(compressedData.size() / 8);
			result.resize(tf.GetLength() / 8);
			
		}
		else {
			//result.resize(compressedData.size() / 8 + 1);
			result.resize(tf.GetLength() / 8 + 1);
		}
		

		unsigned char cur_char = 0;
		int deg = 7;
		size_t result_counter = 0;

		//for (size_t i = 0; i < compressedData.size(); i++) {
		//	cur_char += (((unsigned char)compressedData[i]) << deg);
		//
		//	if (deg > 0) {
		//		deg--;
		//	}
		//	else {
		//		deg = 7;
		//		result[result_counter] = cur_char;
		//		result_counter++;
		//		cur_char = 0;
		//	}
		//}

		for (size_t i = 0; i < tf.GetLength(); i++) {
			cur_char += (((unsigned char)tf.GetBit(i)) << deg);
		
			if (deg > 0) {
				deg--;
			}
			else {
				deg = 7;
				result[result_counter] = cur_char;
				result_counter++;
				cur_char = 0;
			}
		}

		if (deg < 7) result[result_counter] = cur_char;

		return result;
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