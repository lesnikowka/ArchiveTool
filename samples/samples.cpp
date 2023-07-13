#include "../include/Archiver.h"
#include "../include/File.h"
#include "../include/Unpacker.h"
//#include ""../include/LZ77.h"

#include <iostream>
#include <fstream>
#include <ctime>




int main() {
	std::string dir = "/home/nik/data/";
	std::string outdir = "/home/nik/data/out/";
	std::string decdir = "/home/nik/data/dec/";
	std::string name = "1";
	std::string name_aft_pack = "1.txt.lzhf";
	
	int start = std::clock();

	Archiver arch;
	arch.addFile(dir + name);
	arch.compress();
	arch.save(outdir);
	
	int end = std::clock();

	std::cout << "TIME: " << (end - start) / CLOCKS_PER_SEC << " seconds\n\n";
	


	//Unpacker unp;
	//unp.addFile(outdir + name_aft_pack);
	//unp.unpack();
	//unp.save(decdir);
	
	//std::cout << "TEST MY PROGRAM" << std::endl << std::endl << std::endl;


}