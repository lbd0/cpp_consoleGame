#pragma once
#include "Item.h"
#include "RainCoat.h"
#include "WetWipes.h"
#include  "ConsoleManager.h"
#include <map>

class Inventory
{
private:
	map<Item*, int> invenItem;
	int count;
	ConsoleManager console;
public:
	Inventory();
	~Inventory();
	map<Item*,int> GetItem();
	void SetCnt(Item* i, int n);
	Item* AddItem(int type);
	bool UseItem(const ItemType& type);
	void ShowCnt();
	void ShowInven();
};

