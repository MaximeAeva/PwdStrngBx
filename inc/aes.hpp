#ifndef AES_H
#define AES_H

#include <iostream>
#include <bitset>

typedef std::bitset<8> byte;  
typedef std::bitset<32> word;  
  
const int Nr = 10;  
const int Nk = 4;    
  
void KeyExpansion(byte key[4*Nk], word w[4*(Nr+1)]);

void encrypt(byte in[4*4], word w[4*(Nr+1)]);

void decrypt(byte in[4*4], word w[4*(Nr+1)]);

#endif