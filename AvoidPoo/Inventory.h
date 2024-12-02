#pragma once
#include "Item.h"
#include  "ConsoleManager.h"
#include <map>

class Inventory
{
private:
	map<Item*, int> invenItem;
	int count;
	ConsoleManager console;
public:
	Inventory() :count(0) {}
	void AddItem(Item* item);
	void UseItem(const ItemType& type);
	void ShowCnt();
	void ShowInven() const;
};

