#include "io.hpp"

bool existence()
{
    std::fstream file("./res/.sfdb");
    if(file.good())
        return true;
    return false;
}

void writeFile(byte* array)
{
    std::fstream file;
    file.open("./res/.sfdb", std::ios::app);
	if (!file) {
		std::cout << "File not created!";
	}
	else {
        file << '\n';
		for(int i=0; i<16; ++i) 
        { 
            file << std::hex << array[i].to_ulong() << std::dec << " ";
        }
		file.close();
	}
}

