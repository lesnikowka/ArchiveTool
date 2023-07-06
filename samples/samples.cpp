#include <iostream>
#include "Archiver.h"
#include "File.h"
#include <fstream>
//#include <LZ77.h>
#include <Unpacker.h>


int main() {
	std::string dir = "C:/Users/Nikita/Desktop/data/";
	std::string outdir = "C:/Users/Nikita/Desktop/data/out/";
	std::string decdir = "C:/Users/Nikita/Desktop/data/dec/";
	std::string name = "1.txt";
	std::string name_aft_pack = "1.txt.lz77";
	std::string pname = "2.pdf";
	std::string pname_aft_pack = "2.pdf.lz77";

	Archiver<LZ77> arch;
	arch.addFile(dir + pname);
	arch.compress();
	arch.save(outdir);

	Unpacker<LZ77> unp;
	unp.addFile(outdir + pname_aft_pack);
	unp.unpack();
	unp.save(decdir);



}