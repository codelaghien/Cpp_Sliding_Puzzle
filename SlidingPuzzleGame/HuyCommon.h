#pragma once
using namespace std;
#include <iostream>
#include <windows.h>
#include <string>
#include <codecvt>
#include <locale>
#include <conio.h>   
#include <vector>

class MyCommon
{ 
    public:
		static wstring trim(wstring str);
		static string trim(string str); 
};
