#pragma once
#include "Item.h"
#include <map>

class Inventory
{
private:
	map<Item*, int> invenItem;
	int count;
public:
	Inventory() :count(0) {}
	void AddItem(Item* item);
	void UseItem(const ItemType& type);
	
	void ShowInven() const;
};

