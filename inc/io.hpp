#ifndef IO_H
#define IO_H

#include <iostream>
#include <fstream>
#include <bitset>
#include <string>
#include <cmath>

typedef std::bitset<8> sbyte;   

bool existence();
void writeFile(sbyte *array);
bool readFile(sbyte *array, int line);


#endif