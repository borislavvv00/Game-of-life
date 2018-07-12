#include <iostream>
#include <Windows.h>
#define COLONS 55
#define ROWS 55

using namespace std;

/*
	I use two arrays (map, newMap) for each frame. 
	At the beginning map has a figure in it and newMap is full with spaces.
	Firstly, I check surrounding cells of each cell in map and then full newMap with live and dead cells (live cell ".", dead cell " ").
	Secondly, map takes all values from newMap.
	Finally, all steps are repeated for each frame.
*/

char map[COLONS][ROWS];
int countLiveCells = 0;//count live cells near the current one cell
bool isNewMapFull = false;
char newMap[COLONS][ROWS];

void FullingNewMap()
{
	//Full newMap with spaces
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
	//Full map with the start figure
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
	/* 
		Decides if the current cell to be live or dead
		And full newMap with them 
	*/
	if (countLiveCells < 2 || countLiveCells > 3)
	{
		//Dead cell
		newMap[i][j] = ' ';
	}
	else if (countLiveCells == 3)
	{
		//Live cell
		newMap[i][j] = '.';
	}
}

void CheckingForLiveCells(int i, int j)
{
	/* 
		Check cells in the range of map
		h and k are used to check the surrounding 8 cells
	*/
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
						//Count live cells around the current one cell
						countLiveCells++;
						if (h == 1)
						{
							//When the last cell around the current one is count
							Rules(i, j);
						}
					}
				}
				else if (map[i + h][j + k] == ' ')
				{
					if (i + h != i || j + k != j)
					{
						//Count live cells around the current one cell
						if (h == 1)
						{
							//When the last cell around the current one is count
							Rules(i, j);
						}
					}
				}
			}
		}
	}
	//Reset countLiveCells for the next cell 
	countLiveCells = 0;
}

void FullingMap()
{
	//Full map with live and dead cellss
	for (int i = 0; i < COLONS; i++)
	{
		for (int j = 0; j < ROWS; j++)
		{
			if (isNewMapFull == false)
			{
				StartFigure(i, j);
			}
			else if (isNewMapFull == true)
			{
				CheckingForLiveCells(i, j);
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
			if (isNewMapFull == true)
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
		if (isNewMapFull == false)
		{
			FullingNewMap();
		}
		FullingMap();
		OutputingMap();
		isNewMapFull = true;
		ClearScreen();
		Sleep(700);
	}

	return 0;
}
