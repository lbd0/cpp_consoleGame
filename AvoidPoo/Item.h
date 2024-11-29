#pragma once
#include <iostream>
#include "Unit.h"
using namespace std;

class Item
{
protected:
	int price;
	string name;
	string desc;
	ItemType type;
public:
	Item(const string& n, const int p, const string& d, const ItemType& t) :name(n), price(p), desc(d), type(t) {}
	Item():name("NONE"), price(0), desc("NONE"), type(ItemType::NONE) {}

	int GetPrice() { return price; }
	string GetName() { return name; }
	string GetDesc() { return desc; }
	ItemType GetType() { return type; }

	virtual void Skill() { cout << "Item Å¬·¡½º"; }

	bool operator< (const Item& item) const
	{
		return this->type < item.type;
	}

	bool operator== (const Item& item) const
	{
		return this->type == item.type;
	}
};

