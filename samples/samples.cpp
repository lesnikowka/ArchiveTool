#include <iostream>
#include "Archiver.h"
#include "File.h"
#include <fstream>
//#include <LZ77.h>
#include <Unpacker.h>

void writeNext(std::string& data, unsigned long long last_replace, unsigned next) {
	for (int i = 0; i < 4; i++) {
		unsigned shifted_next = (next << (8 * i)) >> 24;
		char c = shifted_next;

		data[last_replace + 8 + i] = c;
	}
}

unsigned get_int(const std::string& data, size_t pos) {
	if (pos + 4 > data.size()) {
		throw std::range_error("index out of the bounds");
	}

	unsigned result = 0;

	for (int i = 0; i < 4; i++) {
		unsigned a = (unsigned char)data[pos + i];
		a = a << (24 - 8 * i);

		result += ((unsigned)data[pos + i]) << (24 - 8 * i);
	}

	return result;
}

int main() {
	std::string dir = "C:/Users/Nikita/Desktop/data/";
	std::string outdir = "C:/Users/Nikita/Desktop/data/out/";
	std::string decdir = "C:/Users/Nikita/Desktop/data/dec/";
	std::string name = "1.txt";
	std::string name_aft_pack = "1.txt.lz77";
	std::string pname = "1.pdf";
	std::string pname_aft_pack = "1.pdf.lz77";
	
	Archiver<LZ77> arch;
	arch.addFile(dir + pname);
	arch.compress();
	arch.save(outdir);
	
	Unpacker<LZ77> unp;
	unp.addFile(outdir + pname_aft_pack);
	unp.unpack();
	unp.save(decdir);
	
	//std::string s = "aaaaaaaaaaaa";
	//for (unsigned i = 0; i < 1000000; i++) {
	//	writeNext(s, 0, i);
	//	unsigned h = get_int(s, 8);
	//	if (h != i) {
	//
	//	}
	//}
	


}