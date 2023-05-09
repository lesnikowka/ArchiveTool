#pragma once
#include "CompressionAlgorithm.h"
#include <vector>


class Haffman : public CompressionAlgorithm {
public:
	Haffman() = default;

	std::string encode(const std::string& data) override {
		return std::string();
	}

	std::string decode(const std::string& data) override {
		return std::string();
	}
private:
	std::vector<int> collectFrequency(const std::string& data) {
		std::vector<int> frequency(256);

		for (char c : data) {
			frequency[(unsigned char)c]++;
		}

		return frequency;
	}

	std::vector<std::vector<bool>> createHaffmanCodes(const std::vector<int> frequency) {
		std::vector<std::vector<bool>> haffmanTable(256);

	}

};