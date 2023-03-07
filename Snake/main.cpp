#include <iostream>
#include <windows.h>
#include <conio.h>
#include <string>
#include <cstdlib>
#include <ctime>


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

    public: string ToString()
    {
        return to_string(x) + " " + to_string(y);
    }

    public: void AddVector(Vector2 vector2)
    {
        x = x + vector2.x;
        y = y + vector2.y;
    }

    public: bool Compare(Vector2 vector2)
    {
       return (x == vector2.x && y == vector2.y);
    }
};

HANDLE hConsole;
bool isMenu;
int height,width;
int score;
Vector2 playerPos(0,0);
Vector2 fruitPos(0,0);
Vector2 direction(1,0);

void Restart()
{
    score = 0;
    playerPos = Vector2(width/2,height/2);
    fruitPos = Vector2(rand() % (width - 2) + 1,rand() % (height - 2) + 1);
}
void SetUp()
{
    score = 0;
    height = 20;
    width = 30;
    srand(time(nullptr));
    playerPos = Vector2(width/2,height/2);
    fruitPos = Vector2(rand() % (width - 2) + 1,rand() % (height - 2) + 1);

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
            case 'a': direction = Vector2(-1,0);
                break;
            case 'd': direction = Vector2(1,0);
                break;
            case 's': direction = Vector2(0,1);
                break;
            case 'w': direction = Vector2(0,-1);
                break;
        }
    }


}

void CheckHitBoxes()
{
    if(playerPos.Compare(fruitPos))
    {
        score ++;
        fruitPos = Vector2(rand() % (width - 2) + 1,rand() % (height - 2) + 1);
    }

    if(playerPos.x > width || playerPos.x < 0 || playerPos.y < 0 || playerPos.y > height)
    {
        Restart();
    }
}

void UpdateFrame()
{
    system("cls");
    playerPos.AddVector(direction);
    CheckHitBoxes();

    SetConsoleTextAttribute(hConsole, 4);
    cout << "          SCORE: " << score;
    for(int i = 0; i < height + 3;i++)
    {
        cout << "\n";
        for(int j = 0; j< width + 5;j++)
        {
            SetConsoleTextAttribute(hConsole, 68);
            if(playerPos.x == j - 2 && playerPos.y == i - 1)
            {
               SetConsoleTextAttribute(hConsole, 2);
               cout << "O";
               SetConsoleTextAttribute(hConsole, 4);
            }
            else if(fruitPos.x == j - 2 && fruitPos.y == i - 1)
            {
               SetConsoleTextAttribute(hConsole, 2);
                cout << "$";
                SetConsoleTextAttribute(hConsole, 4);
            }
            else
            {
                if((i == 0 || i == height + 2) || (j <= 1 || j >= width + 3))
                {
                    cout << "#";
                //    if(isMenu)Sleep(5);
                }
                else
                {
                    SetConsoleTextAttribute(hConsole,0);
                    cout << " ";
                }
            }
        }
        SetConsoleTextAttribute(hConsole,0);
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
            GetKeys();
            UpdateFrame();
            Sleep(10);
        }

    }
    return 0;
}
