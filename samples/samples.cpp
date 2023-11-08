#include <iostream>
#include "Archiver.h"
#include "File.h"
#include <fstream>
#include <LZ77.h>
#include <Unpacker.h>
#include <ctime>

int main() {

	std::string dir = "C:/Users/lesni/Desktop/compression/";
	std::string outdir = "C:/Users/lesni/Desktop/compression/";
	std::string decdir = "C:/Users/lesni/Desktop/compression/dec/";
	std::string name = "1.pdf";
	std::string name_aft_pack = name + ".ajr";

	int start = std::clock();

	Archiver arch;
	arch.addFile(dir + name);
	arch.addFile(dir + "2.pdf");
	//arch.addFile(dir + "1.mp4");
	arch.compress();
	arch.save(outdir);

	int end = std::clock();

	std::cout << "Time: " << (end - start) / CLOCKS_PER_SEC << " seconds" << std::endl;

	start = std::clock();

	Unpacker unp;
	unp.addFile(outdir + name_aft_pack);
	unp.addFile(outdir + "2.pdf.ajr");
	//unp.addFile(outdir + "1.mp4.ajr");
	unp.unpack();
	unp.save(decdir);

	end = std::clock();

	std::cout << "Time: " << (end - start) / CLOCKS_PER_SEC << " seconds" << std::endl;


}