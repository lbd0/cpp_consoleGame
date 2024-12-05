#include "Poo.h"

Poo::Poo()
{ }

// ¶Ë ¶³¾îÁö´Â ÇÔ¼ö
bool Poo::MovePoo(int& x, int& y, int speed)
{
	if (y < 60) {
		if ((y - speed) < 10) console.ErasePoo(x, y);
		else console.ErasePoo(x, y-speed);
		console.DrawPoo(x, y);
	}
	else {
		console.ErasePoo(x, y- speed);
		return true;
	}
	y+=speed;
	return false;
}





