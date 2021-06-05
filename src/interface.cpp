#include "interface.hpp"

word w[4*(Nr+1)] = {}; 

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
    OpenClipboard(0);
    EmptyClipboard();
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

void sideMenu(int current, int item, int LINES, int inter = 0)
{
    int state = 0;
    char array[17] = {};
    if(item>4) 
    {
        if(!current)
            item = 1;
        else
            item = 0;
    }
    else if(item<0)
    {
        if(current == 4)
            item = 3;
        else
            item = 4;
    }
    for(int i = 0; i<5; i++)
    {
        if(i==current)  
            colorMenu(menutxt[i], LINES/3+i, 2);
        else if(i==item)
            colorMenu(menutxt[i], LINES/3+i, 1);
        else
           colorMenu(menutxt[i], LINES/3+i, 0); 
    }
    if(inter) return;
    while(!state)
    {
        int ch = _getch ();
        if (ch == 0 || ch == 224)
        {
            switch (_getch ())
            {
                case 72:
                    state = 1;
                    break;
                case 80:
                    state = 2;
                    break;
                case 77:
                    state = 3;
                    break;
            }
        }
    }
    if(state==1)
    {
        if(item-1==current)
            sideMenu(current, item-2, LINES);
        else
            sideMenu(current, item-1, LINES);
    }
    else if(state==2)
    {
        if(item+1==current)
            sideMenu(current, item+2, LINES);
        else
            sideMenu(current, item+1, LINES);
    }
    else
    { 
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
}

void design(std::string page)
{
    CONSOLE_SCREEN_BUFFER_INFO csbiInfo;
    GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbiInfo);
    int COLS = csbiInfo.dwSize.X;
    int LINES = csbiInfo.srWindow.Bottom;

    int parm1;
    int parm2;

    border(COLS, LINES);

    if(page=="home")
    {
        parm2 = -1;
        char array[17] = {};
        sbyte key[17] = {};
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
        parm1 = 0;
        parm2 = 1;
        //Title part
        Reader r("Home");
        for(int i = 0; i<int(r.titleSize.height); i++) 
        {
            gotoxy(int((COLS-2-r.titleSize.width)/2), i+1);
            std::cout << r.text[i];
        }
    }
    else if(page=="search")
    {
        parm1 = -1;
        parm2 = 1;
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
            if(strcmp(plain, cmd) == 0) 
            {
                for(int j = 1; j<2; j++) 
                {
                    readFile(read, i+j);
                    decrypt(read, w);
                    convertToChar(read, plain);
                    gotoxy(int(COLS/2-6), int(LINES/2)+3*j);
                    std::cout << registertxt[j];
                    gotoxy(int(COLS/2-6), int(LINES/2)+(3*j)+1);
                    std::cout << plain;
                    
                }
                readFile(read, i+2);
                decrypt(read, w);
                convertToChar(read, plain);
                const char* output = plain;
                const size_t len = strlen(output) + 1;
                HGLOBAL hMem =  GlobalAlloc(GMEM_MOVEABLE, len);
                memcpy(GlobalLock(hMem), output, len);
                GlobalUnlock(hMem);
                OpenClipboard(0);
                EmptyClipboard();
                SetClipboardData(CF_TEXT, hMem);
                CloseClipboard();
            }
            i+=3;
        }
    }
    else if(page=="add")
    {
        parm1 = -1;
        parm2 = 0;
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
            gotoxy(int(COLS/2-6), int(LINES/3)+3*i);
            std::cout << registertxt[i];

            //Interactions
            gotoxy(int(COLS/2)-8, int(LINES/3)+1+3*i);
            safeinput(content);
            convertToHex(content, hexContent);
            encrypt(hexContent, w);
            writeFile(hexContent);
        }
    }
    else if(page=="list")
    {
        parm1 = 3;
        parm2 = 0;
        //Title part
        Reader r("List");
        for(int i = 0; i<int(r.titleSize.height); i++) 
        {
            gotoxy(int((COLS-2-r.titleSize.width)/2), i+1);
            std::cout << r.text[i];
        }

        sbyte read[16] = {};
        int i = 0;
        while(readFile(read, i))
        {
            char plain[17] = {};
            decrypt(read, w);
            convertToChar(read, plain);
            gotoxy(int(COLS/2-9), int(LINES/3)+int(i/3));
            std::cout << plain;
            i+=3;
        }
    }
    if(parm2!=-1) 
        sideMenu(parm1, parm2, LINES);
    quit();
    return;
}
