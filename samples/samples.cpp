#include <iostream>
#include "Archiver.h"
#include "File.h"
#include <fstream>


unsigned char getSignByte(bool isSimilarSequence, unsigned lenght) {
	assert(lenght <= 127);

	unsigned char result = isSimilarSequence;

	result += (lenght << 1);

	return result;
}

std::pair<bool, unsigned> getLenghtAndIsSimilar(unsigned char c) {
	unsigned char s = c << 7;

	return std::make_pair(s, (c >> 1));
}

class T {
	char* mem;
public:
	T() {
		mem = new char[10];
	}
	const char& operator[](int i) const{
		return mem[i];
	}
};

int main() {
	std::string curdir = "C:/Users/Nikita/Desktop/data/";
	std::string filename = "mir.txt";
	//Archiver arch;
	//arch.addFile("C:/Users/Nikita/Desktop/data/"+filename);
	//arch.compress();
	//arch.save("C:/Users/Nikita/Desktop/data/result_");
	
	Haffman h;
	
	File<std::string> fl = loadFile(curdir + filename);
	auto encoded = h.encode(fl.data);
	File<TBitField> fb(encoded, curdir + filename);
	saveFile(fb, curdir + "result_");
	
	std::string filename2 = "result_mir.txt";
	
	File<TBitField> fu = loadBinaryFile(curdir + filename2);

	//bool b = fu.data == encoded;
	
	File<std::string> fo(h.decode(fu.data), curdir + filename2);
	
	saveFile(fo, curdir + "after_decoding_");

	


}