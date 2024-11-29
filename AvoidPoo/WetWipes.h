#pragma once
#include "Item.h"
class WetWipes : public Item
{
public : 
	WetWipes(const string& n, const int p, const string& d, const ItemType& t) :Item(n, p, d, t) {}
	
	void Skill() override;
};

