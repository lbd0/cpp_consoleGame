#include "Coin.h"

// ���� ������
Coin::Coin(int x, int y)
{
	this->x = x;
	this->y = y;
	// ���� �������� ����
	int p = rand() % 10 + 1;
	price = p;
}

// ���� �������� �Լ�
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

