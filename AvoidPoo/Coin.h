#pragma once
#include "ConsoleManager.h"

class Coin
{
private:
	ConsoleManager console;
	int x;
	int y;
	vector<Coin> coins;
public:
	Coin();
	Coin(int x, int y) : x(x), y(y) {}
	void MoveCoin(int& x, int& y);
	int GetX() const { return x; }
	int GetY() const { return y; }
	void SettingCoin (int n);
};

