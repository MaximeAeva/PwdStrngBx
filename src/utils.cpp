#include "utils.hpp"

void bufferEmptying()
{
    int c = 0;
    while (c != '\n' && c != EOF)
    {
        c = getchar();
    }
}

void safeinput(char *array, int s)
{
    std::cin.get(array, s);
    bufferEmptying();
}

void convertToChar(byte* input, char* array, int s)
{
    int i = 0;
    while(i<s) 
    {
        array[i] = char(input[i].to_ulong());
        i++;
    }
    array[i++] = '\0';
}

void convertToHex(char* array, byte* output)
{
    int loop = 0;
    while(array[loop] != '\0')
    {
        output[loop] = std::bitset<8>(int(array[loop]));
        loop++;
    }
}

void sequencer(char* array, int s)
{
    int c = 0;
    while (c != '\n' && c != EOF)
    {
        c = getchar();
    }
}