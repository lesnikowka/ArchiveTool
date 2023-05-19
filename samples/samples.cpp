#include <iostream>
#include "Archiver.h"
#include "File.h"
#include <fstream>
#include <Unpacker.h>


int main() {
	
	std::string curdir = "C:/Users/Nikita/Desktop/data/";

	Archiver<Haffman> arch;


	arch.addFile(curdir + "mir.txt");

	arch.addFile(curdir + "ar.pdf");

	arch.addFile(curdir + "test.docx");




	arch.compress();

	arch.save(curdir + "c/");

	Unpacker<Haffman> unp;
	
	unp.addFile(curdir + "c/mir.txt.haff");
	//unp.addFile(curdir + "c/ar.pdf.haff");
	//unp.addFile(curdir + "c/test.docx.haff");
	//
	unp.unpack();
	//
	unp.save(curdir + "u/");


}