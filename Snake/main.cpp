#include <iostream>
#include <windows.h>
#include <conio.h>
#include <string>
#include <cstdlib>
#include <ctime>
#include <array>
#include<tuple>


using namespace std;

class Vector2
{
public:
    int x = -1;
    int y = -1;

    Vector2(int posX,int posY)
    {
        x = posX;
        y = posY;
    }

    Vector2()
    {
        x = 0;
        y = 0;
    }

    public: void SetVector(int posX,int posY)
    {
        x = posX;
        y = posY;
    }

    public: void SetVector(Vector2 vector2)
    {
        x = vector2.x;
        y = vector2.y;
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

    public: bool Compare(int posX,int posY)
    {
       return (x == posX && y == posY);
    }
};

HANDLE hConsole;
bool isMenu;
int height,width;

int score;
int lastScore;

char znakPlayer = 219;
char znakFruit = 176;

Vector2 playerPos(0,0);
Vector2 fruitPos(0,0);
Vector2 direction(1,0);

Vector2 *snake;


void Restart()
{
    lastScore = score;
    score = 0;
    playerPos = Vector2(width/2,height/2);
    fruitPos = Vector2(rand() % (width - 2) + 1,rand() % (height - 2) + 1);
}
void SetUp()
{
    score = 0;
    lastScore = 0;
    height = 10;
    width = 10;
    snake =  new Vector2[height*width];
    srand(time(nullptr));
    playerPos = Vector2(width/2,height/2);
    fruitPos = Vector2(rand() % (width - 2) + 1,rand() % (height - 2) + 1);

    hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    isMenu = true;
}
bool CheckSnake1(int x,int y)
{
     for(int index = 0; index < score;index++)
    {
       if(snake[index].Compare(x,y))
       {
           if(index % 2 == 0)
           {
                SetConsoleTextAttribute(hConsole, 7);
           }else
           {
                SetConsoleTextAttribute(hConsole, 8);
           }

        cout << znakPlayer<< znakPlayer;
           return true;
       }
    }
    return false;
}

bool CheckSnake2(int x,int y)
{
     for(int index = 0; index < score;index++)
    {
       if(snake[index].Compare(x,y))
       {
           return true;
       }
    }
    return false;
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
        if(score == 0)
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
        else
        {
            switch(getch())
            {
                case 'a': if(direction.x != 1) direction = Vector2(-1,0);
                    break;
                case 'd': if(direction.x != -1) direction = Vector2(1,0);
                    break;
                case 's': if(direction.y != -1) direction = Vector2(0,1);
                    break;
                case 'w': if(direction.y != 1) direction = Vector2(0,-1);
                    break;
            }
        }
    }


}

void CheckHitBoxes()
{
    if(playerPos.Compare(fruitPos))
    {
        score ++;
        if(score == 1)
        {
            snake[score - 1].SetVector(playerPos.x - direction.x,playerPos.y - direction.y);
        }else
        {
            snake[score - 1].SetVector(snake[score - 2].x - direction.x,snake[score - 2].y - direction.y);
        }

        do
        {
            fruitPos = Vector2(rand() % (width - 2) + 1,rand() % (height - 2) + 1);
        }
        while(CheckSnake2(fruitPos.x,fruitPos.y));
    }

    if(playerPos.x >= width || playerPos.x < 0 || playerPos.y < 0 || playerPos.y >= height)
    {
        Restart();
    }

}

void UpdateFrame()
{
    system("cls");
    if(score > 0)
    {
        for(int index = score -1; index >= 0;index--)
        {
            if(index == 0)
            {
                snake[0].SetVector(playerPos.x,playerPos.y);
            }else
            {
                snake[index].SetVector(snake[index -1]);
            }
        }
    }
    playerPos.AddVector(direction);
    if(CheckSnake2(playerPos.x,playerPos.y))
    {
        Restart();
    }
    CheckHitBoxes();
    SetConsoleTextAttribute(hConsole, 4);

    cout << "    SCORE: " << score << "  |  LAST SCORE: "<< lastScore << endl;
    for(int i =0;i < width +2;i++)
    {
        SetConsoleTextAttribute(hConsole, 68);
        cout << "==";
    }
        cout<< endl;
    for(int j = 0; j < height;j++)
    {
        SetConsoleTextAttribute(hConsole, 68);
        cout << "==";
       for(int i = 0; i < width; i++)
       {
           if(CheckSnake1(i,j));
           else if(playerPos.x == i && playerPos.y == j)
           {
            SetConsoleTextAttribute(hConsole, 9);
            cout << znakPlayer<< znakPlayer;
           }
           else if(fruitPos.x == i && fruitPos.y == j)
           {
            SetConsoleTextAttribute(hConsole, 2);
            cout << znakFruit<< znakFruit;
           }
           else
           {
           SetConsoleTextAttribute(hConsole, 4);
           cout << "  ";
           }
       }
       SetConsoleTextAttribute(hConsole, 68);
       cout << "==" << endl;
    }

    SetConsoleTextAttribute(hConsole, 68);
    for(int i =0;i < width +2;i++)
    {
        cout << "==";
    }

    SetConsoleTextAttribute(hConsole, 1);
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
            Sleep(270);
        }
    }
    return 0;
}
