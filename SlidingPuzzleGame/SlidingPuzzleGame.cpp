// SlidingPuzzleGame.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
#pragma once

#include <iostream>
#include <conio.h> 
#include <string>
#include <algorithm>
#include <windows.h> 
#include <locale>
#include <codecvt>
#include <cstdlib>
#include <cstdio>  
#include <fstream>      
#include <stdio.h>      /* printf, scanf, puts, NULL */
#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */ 

#include "HuySize.h";     
#include "HuyCurrentConsole.h";  
#include "HuyWindows.h";  
#include "HuyColors.h";   
#include "Huy_N_Puzzle.h";   

using namespace std;

int main()
{ 
    Huy_N_Puzzle game;
    game.intro();
    game.run();
}
 