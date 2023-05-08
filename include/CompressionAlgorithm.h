#pragma once
#include <string>

class CompressionAlgorithm {
public:
	virtual std::string encode(const std::string& data) = 0;
	virtual std::string decode(const std::string& data) = 0;
};