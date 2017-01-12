#include <iostream>
#include <stdlib.h>
#include <ctime>
#include <conio.h>
#include <windows.h>
#include <stdio.h>

using namespace std;
bool GameOver;
int bonusX, bonusY; 
const int width = 25;
const int height = 15;
int x, y, AIx, AIy;// snake position
int fruitX, fruitY;// fruit position
int score,score1,score2,score3,l;
int coadaX[100], coadaY[100], ncoada;
enum directii { 
STOP = 0, LEFT, RIGHT, UP, DOWN 
};
directii dir;
void Setup()
{
	GameOver = 0;
	dir = STOP;
	x = width/2 ;
	y = height/2;//snake will be centered
	fruitX = rand() % (width);
	fruitY = rand() % (height);
	bonusX = rand() % (width);
	bonusY = rand() % (height);
	//score = 0;
	ncoada = -1;
	l = 50;
}

void Draw()
{
	
	
	//first we need to clear the screen
	system("cls");//claer console window
	
	cout << char(201);
	for (int j=0; j<width; j++)
		cout << char(205);
	cout << char(187);
	cout << endl;
	for (int i = 0; i<height; i++)
	{
		for (int j = 0; j<width; j++)
		{
			if (j == 0)
				cout << char(186);
			if (i == y&&j == x)
				cout << "O";
			else
				if (i == fruitY&&j == fruitX)
					
					cout <<char(232);
				else
					if (i == bonusY&&j == bonusX)
						cout << "B";
				else
				{
					bool print = 0;
					for (int l = 0; l<ncoada; l++)
					{
						if (coadaX[l] == j&&coadaY[l] == i)
						{
							cout << "o";
							print = 1;
						}

					}
					if (print == 0)
						cout << " ";

				}
			if (j == width - 1)
				cout <<char(186);
		}
		cout << endl;
	}
	cout << char(200);
	for (int i = 0; i<width ; i++)
		cout << char(205);
	cout << char(188);
	cout << endl;
	cout << "Score:" << score << endl;
}
void Input()
{//controls
	if (_kbhit())
	{
		switch (_getch())
		{
		
		case 'w':
			if (dir != DOWN)
			dir = UP;
			break;

		case 's':
			if(dir!=UP)
			dir = DOWN;
			break;

		case 'd':
			if(dir!=LEFT)
			dir = RIGHT;
			break;

		case 'a':
			if(dir!=RIGHT)
			dir = LEFT;
			break;

		

			case 'e':
			GameOver = 1;
			break;
		
		case 'p':
			system("pause");
			break;
		}
	}

}

void Logic()
{
	
	int prevX = coadaX[0];
	int prevY = coadaY[0];
	int auxx, auxy;
	coadaX[0] = x;//trebuie sa urmareasca capul
	coadaY[0] = y;
	for (int i = 1; i<ncoada; i++)
	{
		auxx = coadaX[i];
		auxy = coadaY[i];
		coadaX[i] = prevX;
		coadaY[i] = prevY;
		prevX = auxx;
		prevY = auxy;

	}
	switch (dir)
	{case UP:
		
		y--;
		break;
		/*if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
		{
			y--;
		}*/
	case DOWN:
		y++;
		break;

	case LEFT:
		x--;
		break;

	case RIGHT:
		x++;
		break;

	default:
		break;
	}
	//if(x>width || x<0 || y>height || y<0)
	//  GameOver=1;

	if (x >= width)
		x = 0;
	else
		if (x<0)
			x = width - 1;

	if (y >= height)
		y = 0;
	else
		if (y<0)
			y = height - 1;

	for (int i = 0; i<ncoada; i++)
		if (coadaX[i] == x&&coadaY[i] == y)
			GameOver = 1;

	if (x == fruitX &&y == fruitY)
	{

		score += 10;
		fruitX = rand() % width;
		fruitY = rand() % height;
		ncoada++;
		l=l-1;
	}
	if (x == bonusX &&y == bonusY)
	{
		ncoada--;
		bonusX = rand() % (width);
		bonusY = rand() % (height);
		score -= 20;
		
	}
	
}

int main()
{
	score1 = 0;
	score2 = 0;
	score3 = 0;
	HWND console = GetConsoleWindow();
	RECT h;
	GetWindowRect(console, &h);
	MoveWindow(console, h.bottom, h.top, 250, 420, TRUE);
	system("COLOR 2B");
	int ok=1;
	srand(time(NULL));
	while (ok == 1)
	{//RESET:
		Setup();
		ncoada++;
		//system("cls");
		score = 0;
		while (GameOver == 0)
		{
			Draw();
			Input();
			Logic();
			Sleep(l);

		}
		if (score > score1)
		{
			score3 = score2;
			score2 = score1;
			score1 = score;
		}
		else
			if (score > score2)
			{
				score3 = score2;
				score2 = score;
			}
			else
				if (score > score3)
					score3 = score;
		cout << "1." << score1 << endl;
		cout << "2." << score2 << endl;
		cout << "3." << score3 << endl;

		cout << "again?d/n\n";
		char c;
		cin >> c;
		if (c == 'd')
			ok = 1;
		else
		if(c=='n')
			ok = 0;
		//goto RESET;
	}
	
	return 0;
}

