#include <iostream>
#include "../include/Archiver.h"
#include "../include/File.h"
#include <fstream>
//#include ""../include/LZ77.h"
#include "../include/Unpacker.h"


int main() {
	std::string dir = "C:/Users/lesni/OneDrive/������� ����/data/";
	std::string outdir = "C:/Users/lesni/OneDrive/������� ����/data/out/";
	std::string decdir = "C:/Users/lesni/OneDrive/������� ����/data/dec/";
	std::string name = "1.txt";
	std::string name_aft_pack = "1.txt.lzhf";
	std::string pname = "1.pdf";
	std::string pname_aft_pack = "1.pdf.lzhf";
	
	Archiver arch;
	arch.addFile(dir + pname);
	arch.compress();
	arch.save(outdir);
	
	Unpacker unp;
	unp.addFile(outdir + pname_aft_pack);
	unp.unpack();
	unp.save(decdir);
	
	


}