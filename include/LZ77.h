#pragma once

#include <string>
#include <unordered_set>


class LZ77 {
public:
	const size_t SIZE_OF_DICT = 10000;
	const size_t SIZE_OF_BUF = 20;
	const size_t MIN_SEQ_SIZE = 13;

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

		std::unordered_set<size_t> replacements;

		replacements.insert(0);

		for (size_t i = 0; i <= maxSize; i += SIZE_OF_BUF) {
			last_index = i;

			bool concurrency = false;

			for (size_t j = SIZE_OF_BUF; j >= MIN_SEQ_SIZE; j--) {
				std::string word = data.substr(i + SIZE_OF_DICT, j);

				long long place = find(compressed_data, word, SIZE_OF_DICT, replacements);

				if (place != -1) {
					concurrency = true;

					writeNext(compressed_data, last_replace, compressed_data.size() - last_replace);

					last_replace = compressed_data.size();
					
					replacements.insert(last_replace);

					std::string triple = makeTriple(compressed_data.size() - place, j);

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

		unsigned long long triple_index = get_int(compressed_data, 8);

		for (long long i = 12; i < compressed_data.size(); i++) {
			if (triple_index == i) {
				unsigned back = get_int(compressed_data, i);
				unsigned length = get_int(compressed_data, i + 4);
				triple_index += get_int(compressed_data, i + 8);
				
				//decompressed_data += "  INSERT  ";

				decompressed_data += compressed_data.substr(i - back, length);
				i += 11;
			}
			else {
				char c = compressed_data[i];
				decompressed_data += c;
			}
		}

		return decompressed_data;
	}

private:

	long long find(const std::string& source, const std::string& sub, size_t size, const std::unordered_set<size_t> replacements) {
		size_t s = 0;
		for (long long i = source.size(); s < size ; i--) { // del +1 
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

	std::string makeTriple(unsigned back, unsigned n) {
		std::string triple;

		unsigned tmp;

		for (int i = 0; i < 4; i++) {
			tmp = (back << (8 * i)) >> 24;
			triple += tmp;
		}

		for (int i = 0; i < 4; i++) {
			tmp = (n << (8 * i)) >> 24;
			triple += tmp;
		}

		for (int i = 0; i < 4; i++) {
			triple += '\0';
		}

		return triple;
	}

	void writeNext(std::string& data, unsigned long long last_replace, unsigned next) {
		for (int i = 0; i < 4; i++) {
			unsigned shifted_next = (next << (8 * i)) >> 24;
			char c = shifted_next;

			data[last_replace + 8 + i] = c;
		}
	}

	unsigned get_int(const std::string& data, size_t pos) {
		if (pos + 4 > data.size()) {
			throw std::range_error("index out of the bounds");
		} 

		unsigned result = 0;
		
		for (int i = 0; i < 4; i++) {
			unsigned a = data[pos + i];
			a = a << (24 - 8 * i);

			result += ((unsigned)data[pos + i]) << (24 - 8 * i);
		}

		return result;
	}
};