#pragma once
#include "ConsoleManager.h"

class Coin
{
private:
	ConsoleManager console;
	int x;
	int y;
	int price;
	vector<Coin> coins;
public:
	Coin();
	Coin(int x, int y);
	void MoveCoin(int& x, int& y);
	int GetX() const { return x; }
	int GetY() const { return y; }
	int GetPrice() const { return price; }
};

