#include <iostream>
#include <windows.h>
#include <conio.h>

using namespace std;

class Vector2
{
public:
    int x;
    int y;

    Vector2(int posX,int posY)
    {
        x = posX;
        y = posY;
    }
};


HANDLE hConsole;
bool isMenu;

int height,width;
int fruitX,fruitY;

int spawnX,spawnY;
Vector2 spawnPos(0,0);



void SetUp()
{
    height = 21;
    width = 41;
    spawnPos = Vector2(width/2,height/2);

    hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    isMenu = true;
}

void Menu()
{
    Sleep(200);
    system("cls");
    SetConsoleTextAttribute(hConsole, 4);
    cout <<"  ____________________________________"<< endl;
    cout <<" |                                    |"<< endl;
    cout <<" |             S N A K E              |"<< endl;
    cout <<" |____________________________________|"<< endl;
    Sleep(200);
    system("cls");
    SetConsoleTextAttribute(hConsole, 12);
    cout <<"   ________________________________" << endl;
    cout <<"  |                                |"<< endl;
    cout <<"  |            S N A K E           |"<< endl;
    cout <<"  |________________________________|"<< endl;
    SetConsoleTextAttribute(hConsole,15);
    cout <<"          Press any key to play       " << endl;
}

void GetKeys()
{
    if(kbhit())
    {
        switch(getch())
        {
            case 'a': break;


        }

    }


}

void UpdateFrame()
{
    system("cls");
    SetConsoleTextAttribute(hConsole, 4);
    cout << spawnPos.x << " " << spawnPos.y;
    for(int i = 0; i < height ;i++)
    {


        cout << "\n";
        for(int j = 0; j< width;j++)
        {
            if(spawnPos.x == j && spawnPos.y == i)
            {
                SetConsoleTextAttribute(hConsole, 3);
                cout << "@";
                SetConsoleTextAttribute(hConsole, 4);
            }
            else
            {
                if((i == 0 || i == height -1) || (j == 0 || j == width -1))
                {
                    cout << "#";
                    if(isMenu)Sleep(5);
                }
                else
                {
                    cout << " ";
                }
            }
        }
    }

}
int main()
{
    SetUp();
    while(true)
    {
        if(isMenu)
        {
            Menu();
            if(kbhit() && getch())
            {
                UpdateFrame();
                isMenu = false;
            }
        }
        else
        {
            UpdateFrame();
            break;
            Sleep(10);
        }

    }
    return 0;
}
