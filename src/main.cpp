#include <iostream>
#include "utils.hpp"
#include "aes.hpp"

int main()
{
    char array[16];
    char mot[16];
    byte key[16];
    byte plain[16];

    safeinput(array);
    convertToHex(array, key);
    std::cout << std::endl;
    safeinput(mot);
    convertToHex(mot, plain);
    /*byte key[16] = {0x2b, 0x7e, 0x15, 0x16,   
                    0x28, 0x5e, 0xd2, 0xa6,   
                    0xab, 0xf7, 0x15, 0x98,   
                    0x09, 0xcf, 0x4f, 0x3c};  
  
    byte plain[16] = {0x32, 0x88, 0x31, 0xe0,   
                    0x43, 0x5a, 0x31, 0x37,  
                    0xf6, 0x30, 0x98, 0x07,  
                    0xa8, 0x8d, 0xa2, 0x34};*/
    //Output key  
    std::cout << "The key is:";  
    for(int i=0; i<16; ++i)  
        std::cout << std::hex << key[i].to_ulong() << " ";  
    std::cout << std::endl;  
    
    word w[4*(Nr+1)];  
    KeyExpansion(key, w);  
  
    //Output plaintext to be encrypted  
    std::cout << std::endl << "Plaintext to be encrypted:"<< std::endl;  
    for(int i=0; i<16; ++i)  
    {  
        std::cout << std::hex << plain[i].to_ulong() << " ";  
        if((i+1)%4 == 0)  
            std::cout << std::endl;  
    }  
    std::cout << std::endl;  
  
    //Encryption, output ciphertext  
    encrypt(plain, w);  
    std::cout << "Encrypted ciphertext:"<< std::endl;  
    for(int i=0; i<16; ++i)  
    {  
        std::cout << std::hex << plain[i].to_ulong() << " ";  
        if((i+1)%4 == 0)  
            std::cout << std::endl;  
    }  
    std::cout << std::endl;  
  
    //Decrypt, output plaintext  
    decrypt(plain, w);  
    std::cout << "Decrypted plaintext:"<< std::endl;  
    for(int i=0; i<16; ++i)  
    {  
        std::cout << std::hex << plain[i].to_ulong() << " ";  
        if((i+1)%4 == 0)  
            std::cout << std::endl;  
    }  
    std::cout << std::endl; 

    convertToChar(plain, mot); 
    
    std::cout << mot << std::endl;


    return 0;  
}