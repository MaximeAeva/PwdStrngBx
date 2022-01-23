#include "io.hpp"

bool existence()
{
    std::fstream file("./res/.sfdb");
    if(file.good())
        return true;
    return false;
}

void writeFile(sbyte* array, char * f)
{
    std::fstream file;
    file.open(f, std::ios::app);
	if (!file) {
		std::cout << "File not created!";
	}
	else {
		for(int i=0; i<16; ++i) 
        { 
            file << std::hex << array[i].to_ulong() << std::dec << " ";
        }
		file << '\n';
		file.close();
	}
}

bool readFile(sbyte* array, int line, char * f)
{
	int crtLine = 0;
    std::fstream file;
	file.open(f, std::ios::in);
	if (!file) {
		std::cout << "No such file";
	}
	else {
		std::string s;
		while (crtLine<line) 
		{
			if(std::getline(file, s))
				crtLine++;
			else
			{
				return false;
			}
		}
		std::getline(file, s);
		if(s.size()<10) return false;
		int i = 0;
		int numb, count = 0, arrayAdv = 0;
		while(s[i] != '\0')
		{
			if(s[i] != ' ')
				count++;
			else
			{
				numb = 0;
				for(int j = 1; j<count+1; j++)
				{
					switch(s[i-j])
					{
						case 'a':
							numb += 10*pow(16, j-1);
							break;
						case 'b':
							numb += 11*pow(16, j-1);
							break;
						case 'c':
							numb += 12*pow(16, j-1);
							break;
						case 'd':
							numb += 13*pow(16, j-1);
							break;
						case 'e':
							numb += 14*pow(16, j-1);
							break;
						case 'f':
							numb += 15*pow(16, j-1);
							break;
						default:
							numb += int(s[i-j] - '0')*pow(16, j-1);
					}
				}
				array[arrayAdv] = std::bitset<8>(int(numb));
				arrayAdv++;
				count = 0;
			}
			i++;	
		}
	}
	file.close();
	return true;
}



