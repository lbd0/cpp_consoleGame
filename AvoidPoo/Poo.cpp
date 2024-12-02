#include "Poo.h"

void Poo::MovePoo(int& x, int& y)
{
	if (y < 45) {
		console.ErasePoo(x, y - 1);
		console.DrawPoo(x, y);
		//Sleep(100);
		y++;
	}
	else {
		console.ErasePoo(x, y - 1);
		return;
	}
}
