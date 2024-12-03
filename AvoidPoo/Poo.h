#pragma once
#include "ConsoleManager.h"
class Poo
{
private:
	ConsoleManager console;
	int x;
	int y;
public:
	Poo();
	Poo(int x, int y) : x(x), y(y) {}
	void MovePoo(int& x, int& y);
	int GetX() { return x; }
	int GetY() { return y; }
};

