#include <iostream>
#include "Archiver.h"
#include "CompressedFile.h"
#include "FileLoader.h"
#include "RLE-encoder.h"

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

int main() {
	//Archiver arch;
	//arch.addFile("C:/Users/Nikita/Desktop/data/bd.pdf");
	//arch.compress();
	//arch.save("C:/Users/Nikita/Desktop/data/result");

	RLEencoder rlen;
	FileLoader fl("C:/Users/Nikita/Desktop/data/resultbd.pdf");
	std::string afterEncoding = rlen.encode(fl.getData());
	std::ofstream ofs("C:/Users/Nikita/Desktop/data/resultbaafterencoding", std::ios::binary);
	ofs << afterEncoding;

	//std::cout << (int)getLenghtAndIsSimilar( getSignByte(false, 89)).first;

	
}