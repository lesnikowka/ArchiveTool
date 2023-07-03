#pragma once

#include <string>


class LZ77 {
public:
	const size_t SIZE_OF_DICT = 10000;
	const size_t SIZE_OF_BUF = 50;
	const size_t MIN_SEQ_SIZE = 13;

	std::string encode(const std::string& data) {
		std::string resultData;

		long long last_replace = 0;

		resultData += makeTriple(0, 0);

		long long maxSize = (long long)data.size() - (long long)SIZE_OF_BUF - (long long)SIZE_OF_DICT;

		if (maxSize < 0) {
			resultData += data;
		}


		for (long long i = 0; i < maxSize; i += SIZE_OF_BUF) {
			bool concurrency = false;

			for (size_t j = SIZE_OF_BUF; j >= MIN_SEQ_SIZE; j--) {
				std::string word = data.substr(i + SIZE_OF_DICT, j);

				long long place = find(data, word, i, i + SIZE_OF_DICT);

				if (place != -1) {
					concurrency = true;

					writeNext(resultData, last_replace, resultData.size() - last_replace - 1);

					last_replace = resultData.size();
					
					std::string triple = makeTriple(i + SIZE_OF_DICT - place, j);

					resultData += triple;

					resultData += data.substr(i + SIZE_OF_DICT + j, SIZE_OF_BUF - j);
				}
			}

			if (!concurrency) {
				resultData += data.substr(i + SIZE_OF_DICT, SIZE_OF_BUF);
			}
		}

		return resultData;
	}

	std::string decode() {
		return std::string();
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

		triple += (char)(back >> 24);
		triple += (char)((back << 8) >> 24);
		triple += (char)((back << 16) >> 24);
		triple += (char)((back << 24) >> 24);

		triple += (char)(n >> 24);
		triple += (char)((n << 8) >> 24);
		triple += (char)((n << 16) >> 24);
		triple += (char)((n << 24) >> 24);

		triple += (char)0;
		triple += (char)0;
		triple += (char)0;
		triple += (char)0;

		return triple;
	}

	void writeNext(std::string& data, long long last_replace, int next) {
		data[last_replace + 8] = (char)(next >> 24);
		data[last_replace + 9] = (char)((next << 8) >> 24);
		data[last_replace + 10] = (char)((next << 16) >> 24);
		data[last_replace + 11] = (char)((next << 24) >> 24);
	}

};