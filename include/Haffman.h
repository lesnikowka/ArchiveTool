#pragma once
#include "CompressionAlgorithm.h"


class Haffman : public CompressionAlgorithm {
public:
	Haffman() = default;

	std::string encode(const std::string& data) override {
		return std::string();
	}

	std::string decode(const std::string& data) override {
		return std::string();
	}
};