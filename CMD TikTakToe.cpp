// CMD TikTakToe.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"
#include <iostream>
#include <Windows.h>
#include <vector>

#define BEEP_FR 523
#define BEEP_T 200

class Sheet
{
public:
	enum State { EMPTY, X, O };
	struct Pos
	{
		State marker;
		int row;
		int col;
		Pos(int Row, int Col) : row(Row), col(Col) {}
		Pos(char cellno ,State state)
		{
			Pos temp(cellno);
			row = temp.row;
			col = temp.col;
			marker = state;
		}
		Pos(char cellno)
		{
			if (cellno < '4')
			{
				row = 0;
				char temp[2] = { cellno,'\0' };
				col = atoi(temp) - 1;
			}
			else if (cellno < '7')
			{
				row = 1;
				char temp[2] = { cellno,'\0' };
				col = (atoi(temp) - 3) - 1;
			}
			else if (cellno < '9' + 1)
			{
				row = 2;
				char temp[2] = { cellno,'\0' };
				col = (atoi(temp) - 6) - 1;
			}
			else {
				std::cout << "Error Pos\n";
			}
		}
		bool operator == (Pos pos)
		{
			if (row == pos.row && col == pos.col)
			{
				return true;
			}
			return false;
		}
	};
	Sheet()
	{
		for (int i = 0; i < 3; i++)
		{
			for (int j = 0; j < 3; j++)
			{
				grid[i][j] = EMPTY;
			}
		}
	}
	bool displayGrid()
	{
		for (int i = 0; i < 3; i++)
		{
			for (int j = 0; j < 3; j++)
			{
				switch (grid[i][j])
				{
				case EMPTY:
					std::cout << " ";
					break;
				case X:
					std::cout << "X";
					break;
				case O:
					std::cout << "O";
					break;
				default:
					throw "Error";
					break;
				}
				if (j < 2)
				{
					std::cout << " | ";
				}
			}
			if (i < 2)
			{
				std::cout << "\n---------\n";
			}
		}
	}

	bool setValue(Pos pos, State state)
	{
		grid[pos.row][pos.col] = state;
		return true;
	}

	bool win(Pos pos, State state)
	{
		if (pos == Pos('1'))
		{
			if (grid[0][1] == state && grid[0][2] == state)
			{
				return true;
			}
			if (grid[1][1] == state && grid[2][2] == state)
			{
				return true;
			}
			if (grid[1][0] == state && grid[2][0] == state)
			{
				return true;
			}
			return false;
		}
		if (pos == Pos('2'))
		{
			if (grid[0][0] == state && grid[0][2] == state)
			{
				return true;
			}
			if (grid[1][1] == state && grid[2][1] == state)
			{
				return true;
			}
			return false;
		}
		if (pos == Pos('3'))
		{
			if (grid[0][0] == state && grid[0][1] == state)
			{
				return true;
			}
			if (grid[1][2] == state && grid[2][2] == state)
			{
				return true;
			}
			if (grid[1][1] == state && grid[2][0] == state)
			{
				return true;
			}
			return false;
		}
		if (pos == Pos('4'))
		{
			if (grid[0][0] == state && grid[0][2] == state)
			{
				return true;
			}
			if (grid[1][1] == state && grid[1][2] == state)
			{
				return true;
			}
		
			return false;
		}
		if (pos == Pos('5'))
		{
			if (grid[0][1] == state && grid[2][1] == state)
			{
				return true;
			}
			if (grid[1][0] == state && grid[1][2] == state)
			{
				return true;
			}
			if (grid[0][0] == state && grid[2][2] == state)
			{
				return true;
			}
			if (grid[0][2] == state && grid[2][0] == state)
			{
				return true;
			}
			return false;
		}
		if (pos == Pos('6'))
		{
			if (grid[0][2] == state && grid[2][2] == state)
			{
				return true;
			}
			if (grid[1][0] == state && grid[1][1] == state)
			{
				return true;
			}
			return false;
		}
		if (pos == Pos('7'))
		{
			if (grid[0][0] == state && grid[1][1] == state)
			{
				return true;
			}
			if (grid[2][1] == state && grid[2][2] == state)
			{
				return true;
			}
			if (grid[1][1] == state && grid[0][2] == state)
			{
				return true;
			}
			return false;
		}
		if (pos == Pos('8'))
		{
			if (grid[0][1] == state && grid[1][1] == state)
			{
				return true;
			}
			if (grid[2][0] == state && grid[2][2] == state)
			{
				return true;
			}
			return false;
		}
		if (pos == Pos('9'))
		{
			if (grid[0][0] == state && grid[1][1] == state)
			{
				return true;
			}
			if (grid[2][0] == state && grid[2][1] == state)
			{
				return true;
			}
			if (grid[0][2] == state && grid[1][2] == state)
			{
				return true;
			}
			return false;
		}
	}
	State getValue(Pos pos)
	{
		if (pos.row > 2 || pos.col > 2)
		{
			std::cerr << "\nError . . .\n";
			exit(0);
		}
		return grid[pos.row][pos.col];
	}
private:
	State grid[3][3];
};

void gotoXY(int x, int y);
void ClearConsole();

int main()
{
	while (true)
	{
		Sheet sheet;
		Sheet::State currentMarker = Sheet::State::X;
		int  count = 0;
		std::vector<Sheet::Pos> game;
		while (true)
		{
			ClearConsole();
			std::cout << "Welcome to CMD Tik-Tak-Toe\n\n";
			std::cout << "Enter the corresponding cell number to place your marker or '\\q' to quit \nor '\\r' to undo:\n";
			std::cout << "1 | 2 | 3\n---------\n4 | 5 | 6\n---------\n7 | 8 | 9\n\n\n";
			sheet.displayGrid();

			char cellno;
			
			if (currentMarker == Sheet::X)
			{
				std::cout << "\n\nEnter the cell number to place X marker: ";
				std::cin >> cellno;
				if (cellno == '\\')
				{
					char ch = std::cin.get();
					if (ch == 'q')
					{
						exit(1);
					}
					if (ch == 'r')
					{
						if (count < 1)
						{
							Beep(BEEP_FR, BEEP_T);
							continue;
						}
						sheet.setValue(game[count - 1], Sheet::EMPTY);
						game.pop_back();
						currentMarker = Sheet::O;
						count--;
						continue;
					}
				}
				if (sheet.getValue(Sheet::Pos(cellno)) == Sheet::EMPTY)
				{
					sheet.setValue(Sheet::Pos(cellno), Sheet::X);
					game.push_back(Sheet::Pos(cellno, Sheet::X));
					count++;
					if (sheet.win(Sheet::Pos(cellno), Sheet::X))
					{
						gotoXY(0, 11);
						sheet.displayGrid();
						std::cout << "\n\nPLAYER X WON!. . .                                    \n";
						break;
					}
					gotoXY(0, 9);
					sheet.displayGrid();
					currentMarker = Sheet::O;
					continue;
				}
				else
				{
					Beep(BEEP_FR, BEEP_T);
					continue;
				}
			}

			if (currentMarker == Sheet::O)
			{
				std::cout << "\n\nEnter the cell number to place O marker: ";
				std::cin >> cellno;
				if (cellno == '\\')
				{
					char ch = std::cin.get();
					if (ch == 'q')
					{

						exit(1);
					}
					if (ch == 'r')
					{
						if (count < 1)
						{
							Beep(BEEP_FR, BEEP_T);
							continue;
						}
						sheet.setValue(game[count - 1], Sheet::EMPTY);
						game.pop_back();
						currentMarker = Sheet::X;
						count--;
						continue;
					}
				}
				if (sheet.getValue(Sheet::Pos(cellno)) == Sheet::EMPTY)
				{
					sheet.setValue(Sheet::Pos(cellno), Sheet::O);
					game.push_back(Sheet::Pos(cellno, Sheet::X));
					count++;
					if (sheet.win(Sheet::Pos(cellno), Sheet::O))
					{
						gotoXY(0, 11);
						sheet.displayGrid();
						std::cout << "\nPLAYER O WON!. . .                                    \n";
						break;
					}
					gotoXY(0, 9);
					sheet.displayGrid();
					currentMarker = Sheet::X;
				}
				else
				{
					Beep(BEEP_FR, BEEP_T);
					continue;
				}
			
			}
			
		}
		system("pause");
	}
}


void gotoXY(int x, int y)

{

	//Initialize the coordinates

	COORD coord = { x, y };

	//Set the position

	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);

	return;

}

void ClearConsole()

{

	//Get the handle to the current output buffer...

	HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);

	//This is used to reset the carat/cursor to the top left.

	COORD coord = { 0, 0 };

	//A return value... indicating how many chars were written

	//   not used but we need to capture this since it will be

	//   written anyway (passing NULL causes an access violation).

	DWORD count;

	//This is a structure containing all of the console info

	// it is used here to find the size of the console.

	CONSOLE_SCREEN_BUFFER_INFO csbi;

	//Here we will set the current color

	if (GetConsoleScreenBufferInfo(hStdOut, &csbi))

	{

		//This fills the buffer with a given character (in this case 32=space).

		FillConsoleOutputCharacter(hStdOut, (TCHAR)32, csbi.dwSize.X * csbi.dwSize.Y, coord, &count);

		FillConsoleOutputAttribute(hStdOut, csbi.wAttributes, csbi.dwSize.X * csbi.dwSize.Y, coord, &count);

		//This will set our cursor position for the next print statement.

		SetConsoleCursorPosition(hStdOut, coord);

	}

	return;
}
// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
