#ifndef IO_H
#define IO_H

#include <iostream>
#include <fstream>
#include <bitset>

typedef std::bitset<8> byte;   

bool existence();
void writeFile(byte *array);


#endif