#pragma once
#include "CompressionAlgorithm.h"
#include <vector>
#include "HaffmanTreeCreator.h"

class Haffman : public CompressionAlgorithm {
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

	std::string encode(const std::string& data) override {
		HaffmanTreeCreator hc;

		std::vector<int> freq = collectFrequency(data);

		std::vector<std::vector<bool>> codes = hc.createCodes(collectFrequency(data));

		printCodes(codes);

		return std::string();
	}

	std::string decode(const std::string& data) override {
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