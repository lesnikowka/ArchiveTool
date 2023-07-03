#include <iostream>
#include "Archiver.h"
#include "File.h"
#include <fstream>
//#include <LZ77.h>
#include <Unpacker.h>


int main() {
	std::string dir = "C:/Users/Nikita/Desktop/data/";
	std::string outdir = "C:/Users/Nikita/Desktop/data/out/";
	std::string name = "1.txt";

	Archiver<LZ77> arch;

	arch.addFile(dir + name);

	arch.compress();

	arch.save(outdir);


}