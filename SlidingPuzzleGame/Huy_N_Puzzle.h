#pragma once

#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */ 
#include <iostream>
#include <windows.h>
#include <string>
#include <codecvt>
#include <locale>
#include <conio.h>   
#include <vector>

#include "HuyPoint.h"
#include "HuyWindows.h" 
#include "HuyColors.h" 
#include "HuySize.h" 
#include "HuyCurrentConsole.h" 
#include "HuyCommon.h"
using namespace std;

class Huy_N_Puzzle
{
	private:
		HuyWindows _HuyWindows;
		int _Size = 4;
		int _Count = 0;
		int _Width = 13;
		int _Height = 7;
		enum class Direction { UP, RIGHT, DOWN, LEFT };
		int _Board[10][10] = { 0, 0 };
		HuyPoint _Position;
		HuyPoint _EmptyPosition;

	public:
		Huy_N_Puzzle() : Huy_N_Puzzle(4) {};
		Huy_N_Puzzle(int size);
		~Huy_N_Puzzle() {};

		void intro();
		void run();
		void bye();

	private:
		void initBoard();
		void printBottomCommands();
		void alert(wstring title, wstring messages[], int size, bool info = true, string position = "center", int closeTime = 3);
		void randomBoard();
		void drawBoard(); 
		void drawBlock(int value, int row, int col);
		void move(HuyPoint fromPosition, HuyPoint toPostion);
		bool doMove(Direction direction, bool random = false);
		bool isSolved();
		void congratulations();
};

