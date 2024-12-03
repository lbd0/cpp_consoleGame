#include "Coin.h"

void Coin::MoveCoin(int& x, int& y)
{
	if (y < 60) {
		console.EraseCoin(x, y - 1);
		console.DrawCoin(x, y);
	}
	else {
		console.EraseCoin(x, y - 1);
	}
	y++;
}

