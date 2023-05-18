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

int main() {
	std::string filename = "mir.txt";
	//Archiver arch;
	//arch.addFile("C:/Users/Nikita/Desktop/data/"+filename);
	//arch.compress();
	//arch.save("C:/Users/Nikita/Desktop/data/result_");
	
	File fl;
	fl.data = loadData("C:/Users/Nikita/Desktop/data/" + filename);
	fl.directory = "C:/Users/Nikita/Desktop/data/" + filename;
	
	Haffman h;
	
	std::ofstream ofs("C:/Users/Nikita/Desktop/data/after_encoding" + filename, std::ios::binary);
	
	ofs << h.encode(fl.data);

	ofs.close();
	
	

}