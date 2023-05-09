#pragma once
#include "CompressionAlgorithm.h"
#include <vector>
#include <queue>
#include <functional>

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
	class HeapComparator {
	public:
		bool operator()(const std::pair<unsigned char, int>& p1, const std::pair<unsigned char, int>& p2) {
			return p1.second > p2.second;
		}
	};

	std::vector<int> collectFrequency(const std::string& data) {
		std::vector<int> frequency(256);

		for (char c : data) {
			frequency[(unsigned char)c]++;
		}

		return frequency;
	}

	std::vector<std::vector<bool>> createHaffmanCodes(const std::vector<int> frequency) {
		std::vector<std::vector<bool>> haffmanTable(256);
		HeapComparator hp;

		std::priority_queue<std::pair<unsigned char, int>,
			std::vector<std::pair<unsigned char, int>>, HeapComparator> pq(hp);

		for (int i = 0; i < frequency.size(); i++){
			pq.push(std::make_pair(i, frequency[i]));
		}


	}

};