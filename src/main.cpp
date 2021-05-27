#include <iostream>
#include "utils.hpp"
#include "aes.hpp"
#include "io.hpp"

int main()
{
    char array[17];
    char mot[17];
    char motu[17];
    byte key[16];
    byte plain[16];
    byte plain2[16];

    safeinput(array);
    convertToHex(array, key);
    safeinput(mot, 17);
    convertToHex(mot, plain);

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

    writeFile(plain);

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

    convertToChar(plain, motu); 
    
    std::cout << motu << std::endl;

    std::cout << existence() << std::endl;

    return 0;  
}