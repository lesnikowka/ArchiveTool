#pragma once
#include <vector>
#include "HaffmanTreeCreator.h"
#include "tbitfield.h"
#include <unordered_map>
#include <numeric>

std::vector<std::vector<bool>> CODES;
std::vector<size_t> FREQ;
TBitField tb(0);

class Haffman {
	const size_t SIZE_OF_SERVICE_INFO = 16448;
public:
	Haffman() = default;

	void printCodes(std::vector<std::vector<bool>> v) {
		for (int i = 0; i < v.size(); i++) {
			if (v[i].size()) {
				std::cout << (unsigned char)i << ": ";
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
		CODES = codes;
		FREQ = freq;
		//printCodes(codes);

		size_t sizeOfCompressedData = getSizeOfCompressedData(codes, freq);
		TBitField CompressedData(sizeOfCompressedData + SIZE_OF_SERVICE_INFO);


		std::cout << sizeOfCompressedData << std::endl;

		writeValueInBitField(CompressedData, sizeOfCompressedData, 0);

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
		tb = CompressedData;

		return CompressedData;
	}

	std::string decode(const TBitField& t)  {
		TBitField tf = tb;
		if (tf.GetLength() == 0) {
			throw std::invalid_argument("Data is empty");
		}

		size_t sizeOfCompressedData = getValueFromBitField<size_t>(tf, 0);

		std::cout << sizeOfCompressedData << std::endl;

		std::vector<size_t> freq(256);

		size_t bitsize = sizeof(size_t) * 8;

		for (size_t i = bitsize; i < SIZE_OF_SERVICE_INFO; i += bitsize) {
			size_t aa = getValueFromBitField<size_t>(tf, i);
			//std::cout << (i - bitsize) / bitsize << std::endl;
			freq[(i - bitsize) / bitsize] = getValueFromBitField<size_t>(tf, i);	
		}

		//freq = FREQ;

		std::string decompressedData;


		HaffmanTreeCreator hc;
		std::vector<std::vector<bool>> codes = hc.createCodes(freq);

		bool b = codes == CODES;
		bool c = FREQ == freq;

		for (int i = 0; i < freq.size(); i++) {
			std::cout <<"freqs: " << FREQ[i] << " " << freq[i] << std::endl;
		}

		std::unordered_map<std::string, unsigned char> mp;

		for (size_t i = 0; i < codes.size(); i++) {
			if (codes[i].size()) {
				mp.emplace(boolVectorToString(codes[i]), (unsigned char)i);
			}
		}

		std::string current_code = "";

		for (size_t i = SIZE_OF_SERVICE_INFO; i < SIZE_OF_SERVICE_INFO + sizeOfCompressedData; i++) {
			current_code += (unsigned char)tf.GetBit(i);
			auto mp_it = mp.find(current_code);
			if (mp_it != mp.end()) {
				decompressedData += (unsigned char)(*mp_it).second;
				current_code.clear();
			}
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

		int deg = bitsize - 1;
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