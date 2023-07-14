#pragma once

#include "Archiver.h"
#include "Unpacker.h"
#include <iostream>

class ConsoleWindow {
public:
	void Run(int argc, char** argv) {
		if (argc < 3) {
			std::cout << "Too few arguments" << std::endl;
			return;
		}
		std::vector<std::string> directories;

		for (int i = 1; i < argc - 1; i++) {
			directories.push_back(argv[i]);

		}

		std::string outputDirectory(argv[argc - 1]);

		std::cout << "  1) Compressing\n  2) Unpacking\n";

		int choicedAction = 0;

		while (true) {
			std::cin >> choicedAction;

			if (choicedAction != 1 && choicedAction != 2) {
				std::cout << "Incorrect input\n";
			}
			else {
				break;
			}
		}


		if (choicedAction == 1) {
			if (!Compress(directories, outputDirectory)) {
				return;
			}
			
		}
		else if (choicedAction == 2) {
			if (!Unpack(directories, outputDirectory)) {
				return;
			}
		}
	}

	static ConsoleWindow* getInstance() {
		if (instance == nullptr) {
			instance = new ConsoleWindow;
		}
		return instance;
	}

	~ConsoleWindow() {
		delete instance;
		instance = nullptr;
	}

private:
	static ConsoleWindow* instance;

	ConsoleWindow() = default;

	template <class T>
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

			std::cout << "Incorrect output directory" << std::endl;
			return false;
		}

		std::cout << "Done" << std::endl;

		return true;
	}


	bool CompressFiles(Archiver& arch, const std::vector<std::string>& directories, const std::string& outputDirectory) {
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

	bool UnpackFiles(Unpacker& unp, const std::vector<std::string>& directories, const std::string& outputDirectory) {
		std::cout << "Unpacking files..." << std::endl;

		try {
			unp.unpack();
		}
		catch (const std::exception& ex) {
			std::cout << "Program failed" << std::endl;
			return false;
		}

		std::cout << "Done" << std::endl;

		return true;
	}


	bool Compress(const std::vector<std::string>& directories, const std::string& outputDirectory) {
		Archiver arch;

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

	
	bool Unpack(const std::vector<std::string>& directories, const std::string& outputDirectory) {
		Unpacker unp;

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
};


ConsoleWindow* ConsoleWindow::instance = nullptr;