#pragma once

#include <string>
#include <exception>

template <class T>
T getValueFromString(const std::string& data, size_t pos) {
	if (pos + sizeof(T) > data.size()) {
		throw std::range_error("index out of the bounds");
	}

	T result = 0;

	for (int i = 0; i < sizeof(T); i++) {
		result += ((unsigned)(unsigned char)data[pos + i]) << (sizeof(T)*8 - 8 - 8*i);
	}

	return result;
}

template<class T>
void writeValueToString(std::string& data, size_t pos, T value) {
	for (int i = 0; i < sizeof(T); i++) {
		data[pos + i] = (value << (8 * i)) >> (sizeof(T)*8-8);
	}
}