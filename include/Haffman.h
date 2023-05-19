#pragma once
#include <vector>
#include "HaffmanTreeCreator.h"
#include "tbitfield.h"
#include <unordered_map>
#include <numeric>

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

		writeValueInBitField(CompressedData, sizeOfCompressedData, 0);

		int a = sizeOfCompressedData;
		int b = getValueFromBitField<size_t>(CompressedData, 0);

		for (size_t i = 0; i < freq.size(); i++){
			writeValueInBitField(CompressedData, freq[i], sizeof(size_t) * 8 * (1 + i));
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

	std::string decode(const TBitField& tf)  {
		if (tf.GetLength() == 0) {
			throw std::invalid_argument("Data is empty");
		}

		size_t sizeOfCompressedData = getValueFromBitField<size_t>(tf, 0);

		std::vector<size_t> freq(256);

		for (size_t i = sizeof(size_t) * 8; i < SIZE_OF_SERVICE_INFO; i += sizeof(size_t) * 8) {
			freq[(i - sizeof(size_t))/8] = getValueFromBitField<size_t>(tf, i);
		}

		std::string decompressedData;


		size_t a = std::accumulate(freq.begin(), freq.end(), 0);


		decompressedData.resize(a);

		HaffmanTreeCreator hc;
		std::vector<std::vector<bool>> codes = hc.createCodes(freq);

		//printCodes(codes);

		std::unordered_map<std::string, unsigned char> mp;

		for (size_t i = 0; i < codes.size(); i++) {
			mp.emplace(boolVectorToString(codes[i]), (unsigned char)i);
		}

		std::string current_code = "";
		size_t deCompressedDataIt = 0;

		for (size_t i = SIZE_OF_SERVICE_INFO; i < tf.GetLength(); i++) {
			//current_code += tf.GetBit(i);
			//auto mp_it = mp.find(current_code);
			//if (mp_it != mp.end()) {
			//	decompressedData[deCompressedDataIt] = (*mp_it).second;
			//	deCompressedDataIt++;
			//	current_code.clear();
			//}
		}

		return decompressedData;

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
	void writeValueInBitField(TBitField& tf, const T& val, size_t start) {
		size_t bitsize = sizeof(T) * 8;

		for (int i = bitsize-1; i >= 0; i--) {
			if ((val << bitsize - i - 1)>> bitsize - 1){
				tf.SetBit(start + bitsize - i - 1);
			}
		}
	}

	template<class T> 
	T getValueFromBitField(const TBitField& tf, size_t start) {
		size_t bitsize = sizeof(T) * 8;
		T val = 0;

		int deg = sizeof(T) - 1;
		for (size_t i = start; i < start + bitsize; i++) {
			if (tf.GetBit(i)) {
				val += 1 << deg;
			}
			deg--;
		}

		return val;
	}

	std::string boolVectorToString(const std::vector<bool> code) {
		std::string result;
		result.resize(code.size());

		for (size_t i = 0; i < code.size(); i++) {
			result[i] = (unsigned char)code[i];
		}
		
		return result;
	}

	
};