#pragma once

#include <string>
#include <unordered_set>
#include <unordered_map>
#include <set>


class LZ77 {
public:
	static const size_t SIZE_OF_DICT = 32000;
	static const size_t SIZE_OF_BUF = 17;
	static const size_t MIN_SEQ_SIZE = 13;
	static const size_t HASH_SEQUENCE_SIZE = 6;

	static std::string encode(const std::string& data) {
		std::string compressed_data;

		long long last_replace = 0;
		long long last_replace_in_compressed_data = 0;

		compressed_data += makeTriple(0, 0);

		long long maxSize = (long long)data.size() - (long long)SIZE_OF_BUF - (long long)SIZE_OF_DICT;

		if (maxSize < 0) {
			compressed_data += data;

			return compressed_data;
		}
		else {
			compressed_data += data.substr(0, SIZE_OF_DICT);
		}

		long long last_index;

		std::unordered_map<std::string, std::set<size_t>> indexesForSequence;

		addSequences(indexesForSequence, data, 0, SIZE_OF_DICT);

		for (size_t i = 0; i <= maxSize; i += SIZE_OF_BUF) {

			last_index = i;

			bool concurrency = false;

			for (size_t j = SIZE_OF_BUF; j >= MIN_SEQ_SIZE && !concurrency; j--) { 
				std::string word = data.substr(i + SIZE_OF_DICT, j);

				long long place = find(indexesForSequence, data, word, i + SIZE_OF_DICT);

				if (place != -1) {

					concurrency = true; 

					writeNext(compressed_data, last_replace_in_compressed_data, i + SIZE_OF_DICT - last_replace);

					last_replace = i + SIZE_OF_DICT;
					last_replace_in_compressed_data = compressed_data.size();

					std::string triple = makeTriple(i + SIZE_OF_DICT - place, j);

					compressed_data += triple;

					compressed_data += data.substr(i + SIZE_OF_DICT + j, SIZE_OF_BUF - j);

				}
			}

			if (!concurrency) {
				compressed_data += data.substr(i + SIZE_OF_DICT, SIZE_OF_BUF);
			}

			deleteSequences(indexesForSequence, data, i, i + SIZE_OF_BUF);
			addSequences(indexesForSequence, data, i + SIZE_OF_DICT, i + SIZE_OF_DICT + SIZE_OF_BUF);
		}

		if (last_index + SIZE_OF_BUF + SIZE_OF_DICT != data.size()) {
			compressed_data += data.substr(last_index + SIZE_OF_BUF + SIZE_OF_DICT);
		}

		return compressed_data;
	}

	static std::string decode(const std::string& compressed_data) {
		std::string decompressed_data;

		unsigned long long triple_index = get_int(compressed_data, 8);

		decompressed_data += compressed_data.substr(12, SIZE_OF_DICT);

		for (long long i = 12 + SIZE_OF_DICT; i < compressed_data.size(); i++) {

			if (triple_index == decompressed_data.size()) {
				unsigned back = get_int(compressed_data, i);
				unsigned length = get_int(compressed_data, i + 4);
				triple_index += get_int(compressed_data, i + 8);

				decompressed_data += decompressed_data.substr((long long)decompressed_data.size() - back, length);
				i += 11;
			}
			else {
				decompressed_data += compressed_data[i];
			}
		}

		return decompressed_data;
	}

public:
	LZ77() = delete;

	static long long find(const std::unordered_map<std::string, std::set<size_t>>& indexesForSequence, const std::string& data, const std::string& word, size_t current) {
		std::string sequence = word.substr(0, HASH_SEQUENCE_SIZE);

		auto place = indexesForSequence.find(sequence);

		if (place != indexesForSequence.end()) {

			for (auto index = (*place).second.cbegin(); index != (*place).second.cend(); ++index) {

				if (*index <= current - word.size() && data.substr(*index, word.size()) == word) {

					return *index;
				}
			}
		}

		return -1;
	}


	static std::string makeTriple(unsigned back, unsigned n) {
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

	static void writeNext(std::string& data, unsigned long long last_replace, unsigned next) {
		for (int i = 0; i < 4; i++) {
			data[last_replace + 8 + i] = (next << (8 * i)) >> 24;
		}
	}

	static unsigned get_int(const std::string& data, size_t pos) {
		if (pos + 4 > data.size()) {
			throw std::range_error("index out of the bounds");
		}

		unsigned result = 0;

		for (int i = 0; i < 4; i++) {
			result += ((unsigned)(unsigned char)data[pos + i]) << (24 - 8 * i);
		}

		return result;
	}

	static void deleteSequences(std::unordered_map<std::string, std::set<size_t>>& indexesForSequence, const std::string& data, size_t lBound, size_t rBound) {
		for (size_t i = lBound; i < rBound; i++) {
			std::string sequence = data.substr(i, HASH_SEQUENCE_SIZE);

			indexesForSequence[sequence].erase(i);

			if (indexesForSequence[sequence].size() == 0) {
				indexesForSequence.erase(sequence);
			}
		}
	}

	static void addSequences(std::unordered_map<std::string, std::set<size_t>>& indexesForSequence, const std::string& data, size_t lBound, size_t rBound) {
		for (size_t i = lBound; i <= rBound - HASH_SEQUENCE_SIZE; i++) {
			std::string sequence = data.substr(i, HASH_SEQUENCE_SIZE); 

			indexesForSequence[sequence].insert(i);
		}
	}
};