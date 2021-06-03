#ifndef UTILS_H
#define UTILS_H

#include <iostream>
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <bitset>

typedef std::bitset<8> sbyte;   

void safeinput(char *array, int s = 17);

void convertToChar(sbyte* input, char* array, int s = 16);

void convertToHex(char* array, sbyte* output);

void bufferEmptying();

#endif