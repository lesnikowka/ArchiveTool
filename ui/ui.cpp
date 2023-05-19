#include "Archiver.h"
#include "Unpacker.h"
#include <iostream>
#include <unordered_map>



int main(int argc, char **argv) {
	if (argc != 2) {
		std::cout << "Too many arguments" << std::endl;
		return -1;
	}
	std::vector<std::string> directories;

	for (int i = 0; i < argc - 1; i++) {
		directories.push_back(argv[i]);
	}

	std::cout << "1) Compressing\n2) Unpacking\n";

	int choicedAction;

	while(true) {
		std::cin >> choicedAction;

		if (choicedAction != 1 && choicedAction != 2) {
			std::cout << "Incorrect input\n";
		}
	}

	std::unordered_map<std::vector<bool>, unsigned char> mj;

	int algorithmType;

	std::cout << "\t1) Optimal Huffman codes(better)\n\t2)RLE\n";

	while (true) {
		std::cin >> algorithmType;

		if (algorithmType != 1 && algorithmType != 2) {
			std::cout << "Incorrect input\n";
		}
	}

	if (choicedAction == 1) {
		if (algorithmType == 1) {
			Archiver<Haffman> arch;

			try {
				for (int i = 0; i < directories.size(); i++) {
					arch.addFile(directories[i]);
				}
			}
			catch (const std::exception& ex) {
				std::cout << "Incorrect directories" << std::endl;
			}

			try {
				
			}
			catch (const std::exception& ex) {
				std::cout << "Program failed" << std::endl;
				return -1;
			}
		}
	}
}