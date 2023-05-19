#include <vector>
#include "utilites.h"

void printCodes(std::vector<std::vector<bool>> v) {
	for (int i = 0; i < v.size(); i++) {
		if (v[i].size()) {
			std::cout << (unsigned char)i << ": ";
			for (auto e : v[i]) {
				std::cout << e;
			}
			std::cout << std::endl;
		}
	}
}