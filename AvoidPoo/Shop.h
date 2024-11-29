#pragma once
#include "Item.h"
#include "Inventory.h"
#include <vector>

class Shop
{
private:
	vector<Item*> items;

public:
	Shop() {}
	~Shop();
	void BuyItem(const ItemType& type, int& coin, Inventory& inven);
	void AddItem(Item* item);
};

