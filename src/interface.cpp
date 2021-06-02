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


bool sideMenu(int current, int item, int LINES)
{
    int tempo = 0;
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
    while(true)
    {
        tempo++;
        if(GetAsyncKeyState(VK_UP) && tempo>10000)  
            sideMenu(current, item-1, LINES);
        if(GetAsyncKeyState(VK_DOWN) && tempo>10000)   
            sideMenu(current, item+1, LINES);
        if(GetAsyncKeyState(VK_RIGHT) && tempo>2000) 
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
                    return true;
                    break;
            }          
        }
    }
    return false;
}

void design(std::string page)
{
    CONSOLE_SCREEN_BUFFER_INFO csbiInfo;
    GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbiInfo);
    int COLS = csbiInfo.dwSize.X;
    int LINES = csbiInfo.srWindow.Bottom;

    border(COLS, LINES);

    char array[17];
    char cmd[17];

    if(page=="home")
    {
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
        design("homelog");
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

        if(sideMenu(0, 1, LINES));
        {
            quit();
            return;
        }
    }
    else if(page=="search")
    {
        //Title part
        Reader r("Search");
        for(int i = 0; i<int(r.titleSize.height); i++) 
        {
            gotoxy(int((COLS-2-r.titleSize.width)/2), i+1);
            std::cout << r.text[i];
        }

        //Text
        gotoxy(int(COLS/2-16), int(LINES/3));
        std::cout << "1: Home     2: Add     q: Quit";

        gotoxy(int(COLS/2-6), int(LINES/2));
        std::cout << "Command : ";

        //Interactions
        gotoxy(int(COLS/2)-8, int(LINES/2)+1);
        safeinput(cmd);
        if(cmd[0]=='1')
            design("homelog");
        else if(cmd[0]=='2')
            design("add");
        else if(cmd[0]=='q')
        {
            std::cout << "\033[2J";
            system("cls");
            gotoxy(0, 0);
            return;
        }
        else design("search");
            
    }
    else if(page=="add")
    {
        char content[17];
        char user[17];
        char pwd[17];
        //Title part
        Reader r("Add");
        for(int i = 0; i<int(r.titleSize.height); i++) 
        {
            gotoxy(int((COLS-2-r.titleSize.width)/2), i+1);
            std::cout << r.text[i];
        }

        //Text
        gotoxy(int(COLS/2-18), int(LINES/3));
        std::cout << "1: Home     2: Search     q: Quit ";

        gotoxy(int(COLS/2-6), int(LINES/2));
        std::cout << "Command : ";

        //Interactions
        gotoxy(int(COLS/2)-8, int(LINES/2)+1);
        safeinput(cmd);
        if(cmd[0]=='1')
            design("homelog");
        else if(cmd[0]=='2')
            design("search");
        else if(cmd[0]=='q')
        {
            std::cout << "\033[2J";
            system("cls");
            gotoxy(0, 0);
            return;
        }
        else design("add");
            
    }
}
