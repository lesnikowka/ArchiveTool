#include <iostream>
#include "Archiver.h"
#include "File.h"
#include <fstream>
#include <LZ77.h>
#include <Unpacker.h>
#include <ctime>

int main() {

	std::string dir = "C:/Users/lesni/Desktop/data/";
	std::string outdir = "C:/Users/lesni/Desktop/data/";
	std::string decdir = "C:/Users/lesni/Desktop/data/dec/";
	std::string name = "2.pdf";
	std::string name_aft_pack = name + ".ajr";

	int start = std::clock();

	Archiver arch;
	arch.addFile(dir + name);
	arch.compress();
	arch.save(outdir);

	int end = std::clock();

	std::cout << "Time: " << (end - start) / CLOCKS_PER_SEC << " seconds" << std::endl;

	start = std::clock();

	Unpacker unp;
	unp.addFile(outdir + name_aft_pack);
	unp.unpack();
	unp.save(decdir);

	end = std::clock();

	std::cout << "Time: " << (end - start) / CLOCKS_PER_SEC << " seconds" << std::endl;


}