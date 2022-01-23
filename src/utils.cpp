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

void swap (char *a, char *b)
{
    char temp = *a;
    *a = *b;
    *b = temp;
}

void randomize (char arr[], int n)
{
    srand(time(NULL));
    for (int i = n - 1; i > 0; i--)
    {
        int j = rand() % (i + 1);
        swap(&arr[i], &arr[j]);
    }
}

void inputPad(char* tab, int s)
{
    for(int i = 0; i<s; i++)
        tab[i] = char{i+32};        
}


