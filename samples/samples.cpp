#include <iostream>
#include "Archiver.h"
#include "File.h"
#include <fstream>
#include <LZ77.h>
#include <Unpacker.h>
#include <ctime>

int main() {
	//{
	//	LZ77 lz;
	//	std::string s;
	//	s += lz.makeTriple(2e16-10, 2);
	//	lz.writeNext(s, 0, 3);
	//
	//	int a1 = lz.get_int<2>(s, 0);
	//	int a2 = lz.get_int<1>(s, 2);
	//	int a3 = lz.get_int<2>(s, 3);
	//
	//
	//}

	//{
	//	LZ77 lz;
	//	std::unordered_map<std::string, std::set<size_t>> indexesForSequence;
	//
	//	std::string s = "abcdefgigklaiysdaisbdhiasbdhahsdbhahids872837y823ge87g28f7g28fwegw87dsycmn";
	//
	//	lz.addSequences(indexesForSequence, s, 0, s.size());
	//	lz.deleteSequences(indexesForSequence, s, 0, s.size());
	//
	//}



	std::string dir = "C:/Users/lesni/Desktop/";
	std::string outdir = "C:/Users/lesni/Desktop/";
	std::string decdir = "C:/Users/lesni/Desktop/dec/";
	std::string name = "1.pdf";
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