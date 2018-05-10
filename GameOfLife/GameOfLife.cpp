#include <iostream>
#include <Windows.h>
#define COLONS 55
#define ROWS 55

using namespace std;

char map[COLONS][ROWS];
int lifeCells = 0;
bool run = false;
char newMap[COLONS][ROWS];

void FullingNewMap()
{
	for (int i = 0; i < COLONS; i++)
	{
		for (int j = 0; j < ROWS; j++)
		{
			newMap[i][j] = ' ';
		}
	}
}

void ClearScreen()
{
	COORD cursorPosition;
	cursorPosition.X = 0;
	cursorPosition.Y = 0;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), cursorPosition);
}

void StartFigure(int i, int j)
{
	if (((i == 12 || i == 15) && j >= 22 && j <= 26) || ((i == 13 || i == 17) && (j == 22 || j == 26)) || ((i == 14 || i == 16) && (j == 22 || j == 24 || j == 26)) || (i == 18 && (j >= 23 && j <= 25)))
	{
		map[i][j] = '.';
	}
	else
	{
		map[i][j] = ' ';
	}
}

void Rules(int i, int j)
{
	if (lifeCells < 2 || lifeCells > 3)
	{
		newMap[i][j] = ' ';
	}
	else if (lifeCells == 3)
	{
		newMap[i][j] = '.';
	}
}

void ChekingForLifeCells(int i, int j)
{
	if ((i > 0 && i < COLONS - 1) && (j > 0 && j < ROWS - 1))
	{
		for (int h = -1; h <= 1; h++)
		{
			for (int k = -1; k <= 1; k++)
			{
				if (map[i + h][j + k] == '.')
				{
					if (i + h != i || j + k != j)
					{
						lifeCells++;
						if (h == 1)
						{
							Rules(i, j);
						}
					}
				}
				else if (map[i + h][j + k] == ' ')
				{
					if (i + h != i || j + k != j)
					{
						if (h == 1)
						{
							Rules(i, j);
						}
					}
				}
			}
		}
	}
	lifeCells = 0;
}

void FullingMap()
{
	for (int i = 0; i < COLONS; i++)
	{
		for (int j = 0; j < ROWS; j++)
		{
			if (run == false)
			{
				StartFigure(i, j);
			}
			else if (run == true)
			{
				ChekingForLifeCells(i, j);
			}
		}
	}
}

void OutputingMap()
{
	for (int i = 0; i < COLONS; i++)
	{
		for (int j = 0; j < ROWS; j++)
		{
			if (run == true)
			{
				map[i][j] = newMap[i][j];
			}
			cout << map[i][j];
		}
		cout << endl;
	}
}

int main()
{
	while (true)
	{
		if (run == false)
		{
			FullingNewMap();
		}
		FullingMap();
		OutputingMap();
		run = true;
		ClearScreen();
		Sleep(700);
	}

	return 0;
}