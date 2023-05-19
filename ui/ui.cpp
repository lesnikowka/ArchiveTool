#include "Archiver.h"
#include "Unpacker.h"
#include <iostream>

template<class T>
 bool AddFiles(T& arch, const std::vector<std::string>& directories, const std::string& outputDirectory) {
	std::cout << "Loading files..." << std::endl;

	try {
		for (int i = 0; i < directories.size(); i++) {
			arch.addFile(directories[i]);
		}
	}
	catch (const std::exception& ex) {
		std::cout << "Incorrect directories" << std::endl;
		return false;
	}

	std::cout << "Done" << std::endl;

	return true;
}

template<class T>
bool SaveFiles(T& arch, const std::vector<std::string>& directories, const std::string& outputDirectory) {
	std::cout << "Saving files..." << std::endl;

	try {
		arch.save(outputDirectory);
	}
	catch (const std::exception& ex) {
		
		std::cout << "Incorrect output directory (Maybe you should use '/' instead '\\' ever)" << std::endl;
		return false;//
	}

	std::cout << "Done" << std::endl;

	return true;
}

template<class T>
bool CompressFiles(T& arch, const std::vector<std::string>& directories, const std::string& outputDirectory) {
	std::cout << "Compressing files..." << std::endl;

	try {
		arch.compress();
	}
	catch (const std::exception& ex) {
		std::cout << "Program failed" << std::endl;
		return false;
	}

	std::cout << "Done" << std::endl;

	return true;
}

template<class T>
bool UnpackFiles(T& arch, const std::vector<std::string>& directories, const std::string& outputDirectory) {
	std::cout << "Unpacking files..." << std::endl;

	try {
		arch.unpack();
	}
	catch (const std::exception& ex) {
		std::cout << "Program failed" << std::endl;
		return false;
	}

	std::cout << "Done" << std::endl;

	return true;
}

template<class T>
bool Compress(const std::vector<std::string>& directories, const std::string& outputDirectory) {
	Archiver<T> arch;

	if (!AddFiles(arch, directories, outputDirectory)) {
		return false;
	}

	if (!CompressFiles(arch, directories, outputDirectory)) {
		return false;
	}

	if (!SaveFiles(arch, directories, outputDirectory)) {
		return false;
	}

	return true;
}

template<class T>
bool Unpack(const std::vector<std::string>& directories, const std::string& outputDirectory) {
	Unpacker<T> unp;

	if (!AddFiles(unp, directories, outputDirectory)) {
		return false;
	}

	if (!UnpackFiles(unp, directories, outputDirectory)) {
		return false;
	}

	if (!SaveFiles(unp, directories, outputDirectory)) {
		return false;
	}

	return true;
}

bool UnpackAutoCheckExtension(const std::vector<std::string>& directories, const std::string& outputDirectory) {
	std::vector<std::string> rleFiles;
	std::vector<std::string> haffFiles;

	for (const std::string& dir : directories) {
		if (getExtension(dir) == RLE_ARCHIVE_EXTENSION) {
			rleFiles.push_back(dir);
		}
		else if (getExtension(dir) == HAFFMAN_ARCHIVE_EXTENSION) {
			haffFiles.push_back(dir);
		}
		else {
			std::cout << "Incorrect extension" << std::endl;
			return false;
		}
	}

	if (!Unpack<RLE>(rleFiles, outputDirectory)) {
		return false;
	}
	
	if (!Unpack<Haffman>(haffFiles, outputDirectory)) {
		return false;
	}

	return true;
}


int main(int argc, char **argv) {
	if (argc < 3) {
		std::cout << "Too few arguments" << std::endl;
		return -1;
	}
	std::vector<std::string> directories;

	for (int i = 1; i < argc - 1; i++) {
		directories.push_back(argv[i]);
	}

	std::string outputDirectory(argv[argc - 1]);
	
	std::cout << "  1) Compressing\n  2) Unpacking\n";

	int choicedAction = 0;

	while(true) {
		std::cin >> choicedAction;

		if (choicedAction != 1 && choicedAction != 2) {
			std::cout << "Incorrect input\n";
		}
		else {
			break;
		}
	}

	std::unordered_map<std::vector<bool>, unsigned char> mj;

	int algorithmType = 0;

	if (choicedAction == 1) {

		std::cout << "  1) Optimal Huffman codes(better)\n  2) RLE(bad efficient)\n";

		while (true) {
			std::cin >> algorithmType;

			if (algorithmType != 1 && algorithmType != 2) {
				std::cout << "Incorrect input\n";
			}
			else {
				break;
			}
		}
	}

	if (choicedAction == 1) {
		if (algorithmType == 1) {
			if (!Compress<Haffman>(directories, outputDirectory)) {
				return -1;
			}
		}
		else if (algorithmType == 2) {
			if (!Compress<RLE>(directories, outputDirectory)) {
				return -1;
			}
		}
	}
	else if (choicedAction == 2) {
		if (!UnpackAutoCheckExtension(directories, outputDirectory)) {
			return -1;
		}
	}
}

