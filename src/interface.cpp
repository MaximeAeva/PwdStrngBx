#include "interface.hpp"

void gotoxy(int x, int y)
{
    COORD coord;
    coord.X = x;
    coord.Y = y;
    SetConsoleCursorPosition(GetStdHandle( STD_OUTPUT_HANDLE ), coord);
}

void border(int COLS, int LINES)
{
    std::cout << "\033[2J";
    system("cls");
    gotoxy(0, 0);
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

    std::cout << "+";
    for(int col = 0; col < COLS-2; col++)
    {
        std::cout << "=";
    }
    std::cout << "+" << std::endl;

    for(int i = 1; i<LINES-1; i++) 
    {
        std::cout << "|";
        for(int j = 0; j<int(COLS-2); j++) 
            std::cout << " ";
        std::cout << "|";
    }

    std::cout << "+";
    for(int col = 0; col < COLS-2; col++)
    {
        std::cout << "=";
    }
    std::cout << "+" << std::endl;
}

void quit()
{
    std::cout << "\033[2J";
    system("cls");
    gotoxy(0, 0);
}

void colorMenu(std::string text, int line, int color)
{
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    switch(color)
    {
        case 1:
            SetConsoleTextAttribute(hConsole, 240);
            break;
        case 2:
            SetConsoleTextAttribute(hConsole, 128);
            break;
        case 0:
        default:
            SetConsoleTextAttribute(hConsole, 15);
            break;
        
    }
    gotoxy(1, line);
    std::cout << text;
    SetConsoleTextAttribute(hConsole, 15);
}

void sideMenu(int current, int item, int LINES)
{
    int tempo = 0;
    int state = 0;
    if(item==current) item++;
    if(item>4) sideMenu(current, 0, LINES);
    else if(item<0) sideMenu(current, 4, LINES);
    for(int i = 0; i<5; i++)
    {
        if(i==current)  
            colorMenu(menutxt[i], LINES/3+i, 2);
        else if(i==item)
            colorMenu(menutxt[i], LINES/3+i, 1);
        else
           colorMenu(menutxt[i], LINES/3+i, 0); 
    }
    while(!state)
    {
        tempo++;
        if(GetAsyncKeyState(VK_UP) && tempo>10000)  
            state = 1;
        if(GetAsyncKeyState(VK_DOWN) && tempo>10000)   
            state = 2;
        if(GetAsyncKeyState(VK_RIGHT)) 
            state = 3;
    }
    if(state==1)
        sideMenu(current, item-1, LINES);
    else if(state==2)
        sideMenu(current, item+1, LINES);
    else
        switch(item)
            {
                case 0:
                    design("homelog");
                    break;
                case 1:
                    design("search");
                    break;
                case 2:
                    design("add");
                    break;
                case 3:
                    design("list");
                    break;
                default:
                    return;
            }
}

void design(std::string page)
{
    CONSOLE_SCREEN_BUFFER_INFO csbiInfo;
    GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbiInfo);
    int COLS = csbiInfo.dwSize.X;
    int LINES = csbiInfo.srWindow.Bottom;

    border(COLS, LINES);

    if(page=="home")
    {
        char array[17];
        sbyte key[17];
        //Title part
        Reader r("Welcome");
        for(int i = 0; i<int(r.titleSize.height); i++) 
        {
            gotoxy(int((COLS-2-r.titleSize.width)/2), i+1);
            std::cout << r.text[i];
        }

        //Text
        gotoxy(int(COLS/2-6) ,int(LINES/2));
        std::cout << "Enter key:";

        //Interactions
        gotoxy(int(COLS/2)-8, int(LINES/2)+1);
        safeinput(array);
        convertToHex(array, key);
        KeyExpansion(key, w);
    }
    else if(page=="homelog")
    {
        //Title part
        Reader r("Home");
        for(int i = 0; i<int(r.titleSize.height); i++) 
        {
            gotoxy(int((COLS-2-r.titleSize.width)/2), i+1);
            std::cout << r.text[i];
        }
        sideMenu(0, 1, LINES);
        quit();
        return;
    }
    else if(page=="search")
    {
        char cmd[17] = {};
        char plain[17] = {};
        sbyte read[16] = {};
        //Title part
        Reader r("Search");
        for(int i = 0; i<int(r.titleSize.height); i++) 
        {
            gotoxy(int((COLS-2-r.titleSize.width)/2), i+1);
            std::cout << r.text[i];
        }

        gotoxy(int(COLS/2-10), int(LINES/3));
        std::cout << "->";

        //Interactions
        gotoxy(int(COLS/2)-8, int(LINES/3));
        safeinput(cmd);

        int i = 0;
        while(readFile(read, i))
        {
            decrypt(read, w);
            convertToChar(read, plain);
            if(strncmp(plain, cmd, 5) == 0) 
            {
                for(int j = 0; j<3; j++) 
                {
                    readFile(read, i+j);
                    decrypt(read, w);
                    convertToChar(read, plain);
                    gotoxy(int(COLS/2-6), int(LINES/2)+3*j);
                    std::cout << registertxt[j];
                    gotoxy(int(COLS/2-6), int(LINES/2)+(3*j)+1);
                    std::cout << plain;
                }
            }
            i+=3;
        }

        getchar();
    }
    else if(page=="add")
    {
        //Title part
        Reader r("Add");
        for(int i = 0; i<int(r.titleSize.height); i++) 
        {
            gotoxy(int((COLS-2-r.titleSize.width)/2), i+1);
            std::cout << r.text[i];
        }

        for(int i = 0; i<3; i++)
        {
            char content[17] = {};
            sbyte hexContent[16] = {};
            gotoxy(int(COLS/2-6), int(LINES/2));
            std::cout << registertxt[i];

            //Interactions
            gotoxy(int(COLS/2)-8, int(LINES/2)+1);
            safeinput(content);
            convertToHex(content, hexContent);
            encrypt(hexContent, w);
            writeFile(hexContent);
        }
    }
    else if(page=="list")
    {
        char plain[17] = {};
        sbyte read[16] = {};
        //Title part
        Reader r("List");
        for(int i = 0; i<int(r.titleSize.height); i++) 
        {
            gotoxy(int((COLS-2-r.titleSize.width)/2), i+1);
            std::cout << r.text[i];
        }
        int i = 0;
        while(readFile(read, i))
        {
            readFile(read, i);
            decrypt(read, w);
            convertToChar(read, plain);
            gotoxy(int(COLS/2-9), int(LINES/3)+i/3);
            std::cout << plain;
            i+=3;
        }

        getchar();
    }
    design("homelog");
}
