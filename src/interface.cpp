#include "interface.hpp"

int COLS, LINES;
extern word w[4*(Nr+1)]; 
std::default_random_engine generator;
int menuSize = 7;

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

void colorMenu(std::string text, int col, int line, int color)
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
    gotoxy(col, line);
    std::cout << text;
    SetConsoleTextAttribute(hConsole, 15);
}

void sideMenu(int current, int item, int inter = 0)
{
    int state = 0;
    char array[17] = {};
    if(item>menuSize-1) 
    {
        if(!current)
            item = 1;
        else
            item = 0;
    }
    else if(item<0)
    {
        if(current == menuSize-1)
            item = menuSize-2;
        else
            item = menuSize-1;
    }
    for(int i = 0; i<menuSize; i++)
    {
        if(i==current)  
            colorMenu(menutxt[i], 1, LINES/3+i, 2);
        else if(i==item)
            colorMenu(menutxt[i], 1, LINES/3+i, 1);
        else
            colorMenu(menutxt[i], 1, LINES/3+i, 0); 
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
            sideMenu(current, item-2);
        else
            sideMenu(current, item-1);
    }
    else if(state==2)
    {
        if(item+1==current)
            sideMenu(current, item+2);
        else
            sideMenu(current, item+1);
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
                case 4:
                    design("modify");
                    break;
                case 5:
                    design("generate");
                    break;
                default:
                    return;
            }
    }
}

void genMenu(int current, int item, bool* opt, int inter = 0)
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
        if(i==item)
            colorMenu(gentxt[i], COLS/3, LINES/3+i, 1);
        else
            colorMenu(gentxt[i], COLS/3, LINES/3+i, 0); 

        gotoxy(COLS/3+20, LINES/3+i);
        if(i<4 && opt[i]) std::cout << "V";
        else if(i<4 && !opt[i]) std::cout << "X";
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
            genMenu(current, item-2, opt);
        else
            genMenu(current, item-1, opt);
    }
    else if(state==2)
    {
        if(item+1==current)
            genMenu(current, item+2, opt);
        else
            genMenu(current, item+1, opt);
    }
    else
    {
        if(item<4)
        { 
            opt[item] = !opt[item];
            genMenu(current, item, opt);
        }
        else return;
    }
}

void genPad(int current, int item, bool* opt, int inter = 0)
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
        if(i==item)
            colorMenu(gentxt[i], COLS/3, LINES/3+i, 1);
        else
            colorMenu(gentxt[i], COLS/3, LINES/3+i, 0); 

        gotoxy(COLS/3+20, LINES/3+i);
        if(i<4 && opt[i]) std::cout << "V";
        else if(i<4 && !opt[i]) std::cout << "X";
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
            genMenu(current, item-2, opt);
        else
            genMenu(current, item-1, opt);
    }
    else if(state==2)
    {
        if(item+1==current)
            genMenu(current, item+2, opt);
        else
            genMenu(current, item+1, opt);
    }
    else
    {
        if(item<4)
        { 
            opt[item] = !opt[item];
            genMenu(current, item, opt);
        }
        else return;
    }
}

void design(std::string page)
{
    CONSOLE_SCREEN_BUFFER_INFO csbiInfo;
    GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbiInfo);
    COLS = csbiInfo.dwSize.X;
    LINES = csbiInfo.srWindow.Bottom;

    int parm1;
    int parm2;

    border(COLS, LINES);

    if(page=="home")
    {
        parm2 = -1;
        char array[17] = {};
        char pseudoArray[17] = {};
        char charArray[95] = {};
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

        inputPad(charArray, 95);
        randomize(charArray, sizeof(charArray)/sizeof(char));
        for(int l = 0; l<95; l++)
        {
            gotoxy(int(COLS/2-10+(l%19)) ,int(LINES/2+4+(l/19)));   
            std::cout<<charArray[l];
        }
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
        convertToHex(cmd, read);
        encrypt(read, w);
        convertToChar(read, cmd);

        int i = 0;
        while(readFile(read, i))
        {
            convertToChar(read, plain);
            if(strcmp(plain, cmd) == 0) 
            {
                readFile(read, i+1);
                decrypt(read, w);
                convertToChar(read, plain);
                gotoxy(int(COLS/2-10), int(LINES/2));
                std::cout << registertxt[1];
                gotoxy(int(COLS/2-10), int(LINES/2)+1);
                std::cout << plain;

                readFile(read, i+2);
                decrypt(read, w);
                convertToChar(read, plain);
                gotoxy(int(COLS/2-10), int(LINES/2)+3);
                std::cout << "Password :";
                gotoxy(int(COLS/2-10), int(LINES/2)+3+1);
                std::cout << "Password copied to clipboard !";
                //To clipBoard
                const char* output = plain;
                const size_t len = strlen(output) + 1;
                HGLOBAL hMem =  GlobalAlloc(GMEM_MOVEABLE, len);
                memcpy(GlobalLock(hMem), output, len);
                GlobalUnlock(hMem);
                OpenClipboard(0);
                EmptyClipboard();
                SetClipboardData(CF_TEXT, hMem);
                CloseClipboard();

                break;
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
        sbyte reada[16] = {};
        //Title part
        Reader r("List");
        for(int i = 0; i<int(r.titleSize.height); i++) 
        {
            gotoxy(int((COLS-2-r.titleSize.width)/2), i+1);
            std::cout << r.text[i];
        }
        int i = 0;
        while(readFile(reada, i)) i++;
        if(i>10)
        {
            //Miss scroll menu
        }
        sbyte read[16] = {};
        i = 0;
        while(readFile(read, i) && i<31)
        {
            char plain[17] = {};
            decrypt(read, w);
            convertToChar(read, plain);
            gotoxy(int(COLS/2-9), int(LINES/3)+int(i/3));
            std::cout << plain;
            i+=3;
        }
    }
    else if(page=="modify")
    {
        parm1 = -1;
        parm2 = 1;
        char cmd[17] = {};
        char plain[17] = {};
        sbyte read[16] = {};
        char content[17] = {};
        sbyte hexContent[16] = {};
        //Title part
        Reader r("Modify");
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
        convertToHex(cmd, read);
        encrypt(read, w);
        convertToChar(read, cmd);

        gotoxy(int(COLS/2-10), int(LINES/3));
        std::cout << "                  ";

        int i = 0;
        while(readFile(read, i))
        {
            convertToChar(read, plain);
            if(strcmp(plain, cmd) == 0) 
            {
                for(int k = 0; k<3; k++)
                {
                    char content[17] = {};
                    sbyte hexContent[16] = {};
                    gotoxy(int(COLS/2-6), int(LINES/3)+3*k);
                    std::cout << registertxt[k];

                    //Interactions
                    gotoxy(int(COLS/2)-8, int(LINES/3)+1+3*k);
                    safeinput(content);
                    convertToHex(content, hexContent);
                    encrypt(hexContent, w);
                    writeFile(hexContent, "./res/copy.sfdb");
                }
                i+=2;
            }
            else
                writeFile(read, "./res/copy.sfdb");
            i++;
        }
        std::remove("./res/.sfdb");
        std::rename("./res/copy.sfdb", "./res/.sfdb");
    }
    else if(page=="generate")
    {
        parm1 = -1;
        parm2 = 5;
        char cmd[17] = {};
        char p[17] = {};
        sideMenu(parm1, parm2, 1);
        bool opt[4] = {true, true, true, true};
        //Title part
        Reader r("Generate");
        for(int i = 0; i<int(r.titleSize.height); i++) 
        {
            gotoxy(int((COLS-2-r.titleSize.width)/2), i+1);
            std::cout << r.text[i];
        }

        genMenu(-1, 0, opt);
        gotoxy(COLS/3, LINES/3+5);
        std::cout << "Size : ";
        safeinput(cmd, 3);
        int siz = atoi(cmd);
        if(siz<5) siz = 5;
        else if(siz > 16) siz = 16;

        std::uniform_int_distribution<int> distribution(0, 3);

        std::uniform_int_distribution<int> dUp(65,90);
        std::uniform_int_distribution<int> dLow(97,122);
        std::uniform_int_distribution<int> dNumbers(48,57);
        std::uniform_int_distribution<int> spChara(33,47);
        std::uniform_int_distribution<int> spCharb(58,64);
        std::uniform_int_distribution<int> spCharc(91,96);
        std::uniform_int_distribution<int> spChard(123,126);
        std::uniform_int_distribution<int> spChar(1,4);

        int dice_roll;
        int choice[5] = {};
        for(int k = 0; k < siz; k++)
        {
            dice_roll = distribution(generator);
            while(!opt[dice_roll])
                dice_roll = distribution(generator);
            switch (dice_roll)
            {
                case 0:
                    choice[0] = dUp(generator);
                    break;
                case 1:
                    choice[0] = dLow(generator);
                    break;
                case 2:
                    choice[0] = dNumbers(generator);
                    break;
                case 3:
                    choice[1] = spChara(generator);
                    choice[2] = spCharb(generator);
                    choice[3] = spCharc(generator);
                    choice[4] = spChard(generator);
                    choice[0] = choice[spChar(generator)];
                    break;
            }
            p[k] = char(choice[0]);
        }
        gotoxy(int(COLS/2)-8, int(LINES/3)+7);
        const char* output = p;
        const size_t len = strlen(output) + 1;
        HGLOBAL hMem =  GlobalAlloc(GMEM_MOVEABLE, len);
        memcpy(GlobalLock(hMem), output, len);
        GlobalUnlock(hMem);
        OpenClipboard(0);
        EmptyClipboard();
        SetClipboardData(CF_TEXT, hMem);
        CloseClipboard();
        std::cout << "Copied to clipboard !";

    }
    if(parm2!=-1) 
        sideMenu(parm1, parm2);
    quit();
    return;
}

void initializeWindowSize()
{
    system("mode 80,25"); 
    SMALL_RECT WinRect = {0, 0, 80, 20}; 
    SMALL_RECT* WinSize = &WinRect;
    SetConsoleWindowInfo(GetStdHandle(STD_OUTPUT_HANDLE), true, WinSize); 
}
