#include "interface.hpp"

void gotoxy(int x, int y)
{
    COORD coord;
    coord.X = x;
    coord.Y = y;
    SetConsoleCursorPosition(GetStdHandle( STD_OUTPUT_HANDLE ), coord);
}

void design(std::string page)
{
    CONSOLE_SCREEN_BUFFER_INFO csbiInfo;
    GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbiInfo);
    int COLS = csbiInfo.dwSize.X;
    int LINES = csbiInfo.srWindow.Bottom;
    
    char array[17];
    array[0]=1;
    char cmd[17];

    std::cout << "\033[2J";
    system("clear");
    gotoxy(0, 0);
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

    //TOP border
    std::cout << "+";
    for(int col = 0; col < COLS-2; col++)
    {
        std::cout << "=";
    }
    std::cout << "+" << std::endl;

    if(page=="home")
    {
        //Title part
        Reader r("Welcome");
        for(int i = 0; i<int(r.titleSize.height); i++) 
        {
            SetConsoleTextAttribute(hConsole, 15);
            std::cout << "|";
            for(int j = 0; j<int((COLS-3-r.titleSize.width)/2); j++) 
                std::cout << " ";
            SetConsoleTextAttribute(hConsole, 15);
            std::cout << r.text[i];
            for(int j = 0; j<int((COLS-2-r.titleSize.width)-int((COLS-3-r.titleSize.width)/2)); j++) 
                std::cout << " ";
            SetConsoleTextAttribute(hConsole, 15);
            std::cout << "|";
            SetConsoleTextAttribute(hConsole, 15);
        }

        //Space behind title
        for(int i = 0; i<int(LINES-r.titleSize.height-2); i++) 
        {
            SetConsoleTextAttribute(hConsole, 15);
            std::cout << "|";
            for(int j = 0; j<int(COLS-2); j++) 
                std::cout << " ";
            std::cout << "|";
            SetConsoleTextAttribute(hConsole, 15);
        }


        //Bottom border
        std::cout << "+";
        for(int col = 0; col < COLS-2; col++)
        {
            std::cout << "=";
        }
        std::cout << "+" << std::endl;

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
            SetConsoleTextAttribute(hConsole, 15);
            std::cout << "|";
            for(int j = 0; j<int((COLS-3-r.titleSize.width)/2); j++) 
                std::cout << " ";
            SetConsoleTextAttribute(hConsole, 15);
            std::cout << r.text[i];
            for(int j = 0; j<int((COLS-2-r.titleSize.width)-int((COLS-3-r.titleSize.width)/2)); j++) 
                std::cout << " ";
            SetConsoleTextAttribute(hConsole, 15);
            std::cout << "|";
            SetConsoleTextAttribute(hConsole, 15);
        }

        //Space behind title
        for(int i = 0; i<int(LINES-r.titleSize.height-2); i++) 
        {
            SetConsoleTextAttribute(hConsole, 15);
            std::cout << "|";
            for(int j = 0; j<int(COLS-2); j++) 
                std::cout << " ";
            std::cout << "|";
            SetConsoleTextAttribute(hConsole, 15);
        }

        //Bottom border
        std::cout << "+";
        for(int col = 0; col < COLS-2; col++)
        {
            std::cout << "=";
        }
        std::cout << "+" << std::endl;

        //Text
        gotoxy(int(COLS/2-17), int(LINES/3));
        std::cout << "1: Search     2: Add     q: Quit";

        gotoxy(int(COLS/2-6), int(LINES/2));
        std::cout << "Command : ";

        //Interactions
        gotoxy(int(COLS/2)-8, int(LINES/2)+1);
        safeinput(cmd);
        if(cmd[0]=='1')
            design("search");
        else if(cmd[0]=='2')
            design("add");
        else if(cmd[0]=='q')
        {
            std::cout << "\033[2J";
            system("clear");
            gotoxy(0, 0);
            return;
        }
        else design("homelog");
            
    }
    else if(page=="search")
    {
        //Title part
        Reader r("Search");
        for(int i = 0; i<int(r.titleSize.height); i++) 
        {
            SetConsoleTextAttribute(hConsole, 15);
            std::cout << "|";
            for(int j = 0; j<int((COLS-3-r.titleSize.width)/2); j++) 
                std::cout << " ";
            SetConsoleTextAttribute(hConsole, 15);
            std::cout << r.text[i];
            for(int j = 0; j<int((COLS-2-r.titleSize.width)-int((COLS-3-r.titleSize.width)/2)); j++) 
                std::cout << " ";
            SetConsoleTextAttribute(hConsole, 15);
            std::cout << "|";
            SetConsoleTextAttribute(hConsole, 15);
        }

        //Space behind title
        for(int i = 0; i<int(LINES-r.titleSize.height-2); i++) 
        {
            SetConsoleTextAttribute(hConsole, 15);
            std::cout << "|";
            for(int j = 0; j<int(COLS-2); j++) 
                std::cout << " ";
            std::cout << "|";
            SetConsoleTextAttribute(hConsole, 15);
        }

        //Bottom border
        std::cout << "+";
        for(int col = 0; col < COLS-2; col++)
        {
            std::cout << "=";
        }
        std::cout << "+" << std::endl;

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
            system("clear");
            gotoxy(0, 0);
            return;
        }
        else design("search");
            
    }
    else if(page=="add")
    {
        //Title part
        Reader r("Add");
        for(int i = 0; i<int(r.titleSize.height); i++) 
        {
            SetConsoleTextAttribute(hConsole, 15);
            std::cout << "|";
            for(int j = 0; j<int((COLS-3-r.titleSize.width)/2); j++) 
                std::cout << " ";
            SetConsoleTextAttribute(hConsole, 15);
            std::cout << r.text[i];
            for(int j = 0; j<int((COLS-2-r.titleSize.width)-int((COLS-3-r.titleSize.width)/2)); j++) 
                std::cout << " ";
            SetConsoleTextAttribute(hConsole, 15);
            std::cout << "|";
            SetConsoleTextAttribute(hConsole, 15);
        }

        //Space behind title
        for(int i = 0; i<int(LINES-r.titleSize.height-2); i++) 
        {
            SetConsoleTextAttribute(hConsole, 15);
            std::cout << "|";
            for(int j = 0; j<int(COLS-2); j++) 
                std::cout << " ";
            std::cout << "|";
            SetConsoleTextAttribute(hConsole, 15);
        }

        //Bottom border
        std::cout << "+";
        for(int col = 0; col < COLS-2; col++)
        {
            std::cout << "=";
        }
        std::cout << "+" << std::endl;

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
            system("clear");
            gotoxy(0, 0);
            return;
        }
        else design("add");
            
    }
}
