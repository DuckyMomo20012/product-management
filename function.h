#ifndef _FUNCTION_H_
#define _FUNCTION_H_
#include <Windows.h>
#include <iostream>
#include <fstream>
#include <string>
#include <conio.h>
#include <ctime>
using namespace std;
#define TOP 3;
#define LEFT 4;
struct EXP {
	int date = 0, month = 0, year = 0;
};
typedef struct EXP EXP;
struct PRODUCT {
	int year = 0;
	string id, name, exp, company, mfg; // exp: han su dung, mfg: nam san xuat
	EXP date;
	
};
typedef struct PRODUCT PRODUCT;
struct CELL {
	int x, y, m;
};
typedef struct CELL CELL;
void resizeConsole(int width, int height);
void textColor(int x);
void resetData();
void drawBoard();
void tab();
void header();
void move(int x, int y);
void run();
#endif
