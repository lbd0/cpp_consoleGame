#include "Poo.h"

Poo::Poo()
{ }

void Poo::MovePoo(int& x, int& y)
{
	if (y < 60) {
		console.ErasePoo(x, y-1);
		console.DrawPoo(x, y);
	}
	else {
		console.ErasePoo(x, y-1);
	}
	y++;
}





