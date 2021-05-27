#include "utils.hpp"

void safeinput(char *array, int s)
{
    std::cin.get(array, s); 
    std::cin.clear();
    std::cin.ignore(16, '\n');
}

void convertToChar(byte* input, char* array)
{
    int i = 0;
    while(array[i] != '\0') 
    {
        array[i] = char(input[i].to_ulong());
        i++;
    }
}

void convertToHex(char* array, byte* output)
{
    int loop = 0;
    while(array[loop] != '\0')
    {
        output[loop] = std::bitset<8>(int(array[loop]));
        loop++;
    }

    output[loop++] = '\0';
}