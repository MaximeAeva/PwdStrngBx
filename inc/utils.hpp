#ifndef UTILS_H
#define UTILS_H

#include <iostream>
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <bitset>

typedef std::bitset<8> byte;   

void safeinput(char *array, int s = 16);

void convertToChar(byte* input, char* array);

void convertToHex(char* array, byte* output);

#endif