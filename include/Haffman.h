#pragma once
#include <vector>
#include "HaffmanTreeCreator.h"
#include "tbitfield.h"
#include <unordered_map>
#include <numeric>

class Haffman {

	const size_t SIZE_OF_SERVICE_INFO = 16448;

public:
	Haffman() = default;

	TBitField encode(const std::string& data)  {
		HaffmanTreeCreator hc;
		std::vector<size_t> freq = collectFrequency(data);
		std::vector<std::vector<bool>> codes = hc.createCodes(freq);

		size_t sizeOfCompressedData = getSizeOfCompressedData(codes, freq);

		TBitField CompressedData(sizeOfCompressedData + SIZE_OF_SERVICE_INFO);

		writeValueInBitField(CompressedData, sizeOfCompressedData, 0);

		for (size_t i = 0; i < freq.size(); i++){
			writeValueInBitField(CompressedData, freq[i], sizeof(size_t) * 8 * (1 + i));
		}

		size_t i = SIZE_OF_SERVICE_INFO;

		size_t progress = 0;

		for (unsigned char c : data) {
			progress++;
			if (progress % (data.size() / 100) == 0) {
				system("cls");
				std::cout << "Haffman encoding: " << progress * 100 / data.size() << "%" << std::endl;
			}

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

		std::vector<size_t> freq = loadFreq(tf);

		size_t sizeOfCompressedData = getValueFromBitField<size_t>(tf, 0);
		size_t sizeOfDecompressedData = getSizeOfDecompressedData(freq);

		std::string decompressedData;
		decompressedData.resize(sizeOfDecompressedData);


		HaffmanTreeCreator hc;
		std::vector<std::vector<bool>> codes = hc.createCodes(freq);

		std::unordered_map<std::string, unsigned char> mp;

		for (size_t i = 0; i < codes.size(); i++) {
			if (codes[i].size()) {
				mp.emplace(boolVectorToString(codes[i]), (unsigned char)i);
			}
		}

		std::string current_code = "";
		size_t decompressedDataIt = 0;

		size_t prev = decompressedDataIt;

		for (size_t i = SIZE_OF_SERVICE_INFO; decompressedDataIt < sizeOfDecompressedData; i++){

			if (decompressedDataIt % (sizeOfDecompressedData / 100) == 0 && prev != decompressedDataIt) {
				system("cls");
				std::cout << "Haffman decoding: " << decompressedDataIt * 100 / sizeOfDecompressedData << "%" << std::endl;
			}

			prev = decompressedDataIt;


			current_code += (unsigned char)tf.GetBit(i);
			auto mp_it = mp.find(current_code);

			if (mp_it != mp.end()) {
				decompressedData[decompressedDataIt] = (unsigned char)(*mp_it).second;
				current_code.clear();
				decompressedDataIt++;
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
				val += (T)1 << deg;
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

	std::vector<size_t> loadFreq(const TBitField& tf) {
		std::vector<size_t> freq(256);

		size_t bitsize = sizeof(size_t) * 8;

		for (size_t i = bitsize; i < SIZE_OF_SERVICE_INFO; i += bitsize) {
			freq[(i - bitsize) / bitsize] = getValueFromBitField<size_t>(tf, i);
		}

		return freq;
	}

	size_t getSizeOfDecompressedData(const std::vector<size_t> freq) {
		size_t size = std::accumulate(freq.begin(), freq.end(), 0);

		return size;
	}
};