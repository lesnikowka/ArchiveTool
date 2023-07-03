#pragma once

#include <string>


class LZ77 {
public:
	const size_t SIZE_OF_DICT = 10;
	const size_t SIZE_OF_BUF = 3;
	const size_t MIN_SEQ_SIZE = 3;

	std::string encode(const std::string& data) {
		std::string compressed_data;

		long long last_replace = 0;

		compressed_data += makeTriple(0, 0);

		long long maxSize = (long long)data.size() - (long long)SIZE_OF_BUF - (long long)SIZE_OF_DICT;

		if (maxSize < 0) {
			compressed_data += data;
		}
		else {
			compressed_data += data.substr(0, SIZE_OF_DICT);
		}


		long long last_index;

		for (long long i = 0; i < maxSize; i += SIZE_OF_BUF) {
			last_index = i;

			bool concurrency = false;

			for (size_t j = SIZE_OF_BUF; j >= MIN_SEQ_SIZE; j--) {
				std::string word = data.substr(i + SIZE_OF_DICT, j);

				long long place = find(data, word, i, i + SIZE_OF_DICT);

				if (place != -1) {
					concurrency = true;

					writeNext(compressed_data, last_replace, compressed_data.size() - last_replace);

					last_replace = compressed_data.size();
					
					std::string triple = makeTriple(i + SIZE_OF_DICT - place, j);

					compressed_data += triple;

					compressed_data += data.substr(i + SIZE_OF_DICT + j, SIZE_OF_BUF - j);
				}
			}

			if (!concurrency) {
				compressed_data += data.substr(i + SIZE_OF_DICT, SIZE_OF_BUF);
			}
		}

		if (last_index + SIZE_OF_BUF + SIZE_OF_DICT != data.size()) {
			std::string k = data.substr(last_index + SIZE_OF_BUF + SIZE_OF_DICT);
			compressed_data += data.substr(last_index + SIZE_OF_BUF + SIZE_OF_DICT);
		}

		return compressed_data;
	}

	std::string decode(const std::string& compressed_data) {
		std::string decompressed_data;

		long long triple_index = get_int(compressed_data, 8);

		for (long long i = 12; i < compressed_data.size(); i++) {
			if (triple_index == i) {
				int back = get_int(compressed_data, i);
				int length = get_int(compressed_data, i + 4);
				triple_index += get_int(compressed_data, i + 8);
				//decompressed_data += compressed_data.substr(i - back, length);
				i += 12;
			}
			else {
				decompressed_data += compressed_data[i];
			}
		}

		return decompressed_data;
	}

private:

	long long find(const std::string& source, const std::string& sub, size_t lbound, size_t rbound) {
		for (size_t i = lbound; i < rbound - sub.size(); i++) { // del +1 
			bool concurrency = true;
			for (size_t j = 0; j < sub.size(); j++) {
				if (source[i + j] != sub[j]) {
					concurrency = false;
					break;
				}
			}
			if (concurrency) {
				return i;
			}
		}
		return -1;
	}

	std::string makeTriple(int back, int n) {
		std::string triple;

		for (int i = 0; i < 4; i++) {
			triple  += (back << 8 * i) >> 24;
		}

		for (int i = 0; i < 4; i++) {
			triple += (n << 8 * i) >> 24;
		}

		for (int i = 0; i < 4; i++) {
			triple += (char)0;
		}

		return triple;
	}

	void writeNext(std::string& data, long long last_replace, int next) {
		for (int i = 0; i < 4; i++) {
			data[last_replace + 8 + i] = (next << 8 * i) >> 24;
		}
	}

	int get_int(const std::string& data, size_t pos) {
		if (pos + 4 > data.size()) {
			throw std::range_error("index out of the bounds");
		} 

		int result = 0;
		
		for (int i = 0; i < 4; i++) {
			int a = ((int)data[pos + i]) << (24 - 8 * i);
			result += ((int)data[pos + i]) << (24 - 8 * i);
		}

		return result;
	}
};