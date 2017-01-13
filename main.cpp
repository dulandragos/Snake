#include <iostream>
#include <stdlib.h>
#include <ctime>
#include <conio.h>
#include <windows.h>
#include <stdio.h>

using namespace std;
bool GameOver;
int bonus_scorX, bonus_scorY, bonus_speedX, bonus_speedY, bonus_dimX, bonus_dimY; 
const int width = 25;
const int height = 15;
int x, y, AIx, AIy;// snake position
int fruitX, fruitY;// fruit position
long score, score1, score2, score3;
int l, aux, c, aux_coada = -1;
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
	bonus_scorX = rand() % (width);
	bonus_scorY = rand() % (height);
	bonus_speedX = rand() % (width);
	bonus_speedY = rand() % (height);
	bonus_dimX = rand() % (width);
	bonus_dimY = rand() % (height);
	//score = 0;
	ncoada = -1;
	l = 51;
}

void Draw()
{
	c = l;
	if (score != 0)
		aux = score;
	else
		aux = 1;
	system("cls");//clear console window
	cout << endl;
	cout << "          Score:" << score<< endl;
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

					cout << char(232);
				else
					if (i == bonus_scorY&&j == bonus_scorX&&aux%160==0)
						cout << "2";
					else
						if (i == bonus_speedY&&j == bonus_speedX&&aux % 35 == 0&&c>1)
								cout << "S";
						

						else
							if (i == bonus_dimY&&j == bonus_dimX&&aux%7==0)
								cout << "D";
				else
				{
					bool print = 0;
					for (int k = 0; k<ncoada; k++)
					{
						if (coadaX[k] == j&&coadaY[k] == i)
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
	}
	if (x == bonus_scorX &&y == bonus_scorY)
	{
		score *= 2;
		bonus_scorX = rand() % (width);
		bonus_scorY = rand() % (height);
	}
	
	if (x == bonus_speedX &&y == bonus_speedY)
	{
		l -=10;
		
		bonus_speedX = rand() % (width);
		bonus_speedY = rand() % (height);
		ncoada -= 2;
		score += 10;

	}

	if (x == bonus_dimX &&y == bonus_dimY)
	{
		score += 5;
		bonus_dimX = rand() % (width);
		bonus_dimY = rand() % (height);
		ncoada-=1;

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
	MoveWindow(console, h.left, h.top, 390, 470, TRUE);
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
		cout << endl;
		cout << "        Highscores" << endl;
		cout << endl;
		cout << "  1." << score1 << endl;
		cout << "  2." << score2 << endl;
		cout << "  3." << score3 << endl;
		cout << endl;
		cout << "  again?d/n\n";
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

