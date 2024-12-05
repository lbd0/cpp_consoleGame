#include "Coin.h"

// 코인 생성자
Coin::Coin(int x, int y)
{
	this->x = x;
	this->y = y;
	// 가격 랜덤으로 생성
	int p = rand() % 10 + 1;
	price = p;
}

// 코인 떨어지는 함수
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

