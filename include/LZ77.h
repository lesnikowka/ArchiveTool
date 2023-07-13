#pragma once


#include <string>
#include <unordered_set>

#include "StringUtilities.h"

class LZ77 {
public:
	const size_t SIZE_OF_DICT = 500;
	const size_t SIZE_OF_BUF = 13;
	const size_t MIN_SEQ_SIZE = 9;


	std::string encode(const std::string& data) { 

		std::string compressed_data;

		long long last_replace = 0;

		compressed_data.resize(sizeof(unsigned));

		long long maxSize = (long long)data.size() - (long long)SIZE_OF_BUF - (long long)SIZE_OF_DICT;

		if (maxSize < 0) {
			compressed_data += data;
		}
		else {
			compressed_data += data.substr(0, SIZE_OF_DICT);
		}


		long long last_index;

		std::unordered_set<size_t> replacements;

		replacements.insert(0);


		for (size_t i = 0; i <= maxSize; i += SIZE_OF_BUF) {

			if (i % (maxSize / 100) < SIZE_OF_BUF) {
				system("cls");
				std::cout << "LZ77 encoding: " << i * 100 / maxSize << "%" << std::endl;
			}


			last_index = i;

			bool concurrency = false;

			for (size_t j = SIZE_OF_BUF; j >= MIN_SEQ_SIZE && !concurrency; j--) {
				std::string word = data.substr(i + SIZE_OF_DICT, j);

				long long place = find(compressed_data, word, SIZE_OF_DICT, replacements);

				if (place != -1) {

					concurrency = true;

					if (last_replace != 0) {
						writeNext<__int16_t, __int16_t, unsigned>(compressed_data, last_replace, compressed_data.size() - last_replace);
					}
					else {
						writeValueToString<unsigned>(compressed_data, 0, compressed_data.size() - last_replace);
					}

					last_replace = compressed_data.size();

					replacements.insert(last_replace);

					std::string triple = makeTriple<__int16_t, __int16_t, unsigned>(compressed_data.size() - place, j);

					compressed_data += triple;

					compressed_data += data.substr(i + SIZE_OF_DICT + j, SIZE_OF_BUF - j);
				}
			}

			if (!concurrency) {
				compressed_data += data.substr(i + SIZE_OF_DICT, SIZE_OF_BUF);
			}
		}

		if (last_index + SIZE_OF_BUF + SIZE_OF_DICT != data.size()) {
			compressed_data += data.substr(last_index + SIZE_OF_BUF + SIZE_OF_DICT);
		}

		return compressed_data;
	}

	std::string decode(const std::string& compressed_data) {

		std::string decompressed_data;

		size_t triple_index = getValueFromString<unsigned>(compressed_data, 0);

		for (size_t i = sizeof(unsigned); i < compressed_data.size(); i++) {

			if (i % (compressed_data.size() / 100) == 0) {
				system("cls");
				std::cout << "LZ77 decoding: " << i * 100 / compressed_data.size() << "%" << std::endl;
			}

			if (triple_index == i) {
				__int16_t back = getValueFromString<__int16_t>(compressed_data, i);
				__int16_t length = getValueFromString<__int16_t>(compressed_data, i + sizeof(__int16_t));
				triple_index += getValueFromString<unsigned>(compressed_data, i + 2*sizeof(__int16_t));

				decompressed_data += compressed_data.substr(i - back, length);
				i += 2*sizeof(__int16_t) + sizeof(unsigned) - 1;
			}
			else {
				decompressed_data += compressed_data[i];
			}
		}

		return decompressed_data;
	}

private:

	long long find(const std::string& source, const std::string& sub, size_t size, const std::unordered_set<size_t> replacements) {
		size_t s = 0;
		for (long long i = source.size() - 1; s < size; i--) { // del +1 
			if (replacements.find(i - 2) == replacements.end()) {
				bool concurrency = true;
				for (long long j = sub.size() - 1; j >= 0; j--) {
					if (source[i - sub.size() + j + 1] != sub[j]) {
						concurrency = false;
						break;
					}
				}
				if (concurrency) {
					return i - sub.size() + 1;
				}
				s++;
			}
			else {
				i -= 2;
			}
		}
		return -1;
	}
	
	template<class A, class B, class C>
	std::string makeTriple(A back, B n) {
		std::string triple;

		for (int i = 0; i < sizeof(A); i++) {
			triple += (back << (8 * i)) >> (sizeof(A)*8 - 8);
		}

		for (int i = 0; i < sizeof(B); i++) {
			triple += (n << (8 * i)) >> (sizeof(A)*8 - 8);
		}

		for (int i = 0; i < sizeof(C); i++) {
			triple += '\0';
		}

		return triple;
	}


	template<class A, class B, class C>
	void writeNext(std::string& data, size_t last_replace, C next) {
		writeValueToString<C>(data, last_replace + sizeof(A) + sizeof(B), next);
	}
};