#pragma once
#include "Item.h"

class RainCoat : public Item
{
public :
	RainCoat(const string& n, const int p, const string& d, const ItemType& t) : Item(n, p, d, t) {}

	void Skill() override;
};

