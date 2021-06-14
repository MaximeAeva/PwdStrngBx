#include "utils.hpp"

void safeinput(char *array, int s)
{
    std::cin.sync();
    std::cin.get(array, s);
}

void convertToChar(sbyte* input, char* array, int s)
{
    int i = 0;
    while(i<s) 
    {
        array[i] = char(input[i].to_ulong());
        i++;
    }
    array[i++] = '\0';
}

void convertToHex(char* array, sbyte* output)
{
    int loop = 0;
    while(array[loop] != '\0')
    {
        output[loop] = std::bitset<8>(int(array[loop]));
        loop++;
    }
}


