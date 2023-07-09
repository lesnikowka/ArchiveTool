#include <iostream>
#include "Archiver.h"
#include "File.h"
#include <fstream>
//#include <LZ77.h>
#include <Unpacker.h>


int main() {
	std::string dir = "C:/Users/lesni/OneDrive/Рабочий стол/data/";
	std::string outdir = "C:/Users/lesni/OneDrive/Рабочий стол/data/out/";
	std::string decdir = "C:/Users/lesni/OneDrive/Рабочий стол/data/dec/";
	std::string name = "1.txt";
	std::string name_aft_pack = "1.txt.ajr";
	std::string pname = "1.pdf";
	std::string pname_aft_pack = "1.pdf.ajr";
	
	Archiver arch;
	arch.addFile(dir + pname);
	arch.compress();
	arch.save(outdir);
	
	Unpacker unp;
	unp.addFile(outdir + pname_aft_pack);
	unp.unpack();
	unp.save(decdir);
	
	


}