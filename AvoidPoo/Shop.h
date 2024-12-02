#pragma once
#include "Item.h"
#include "RainCoat.h"
#include "WetWipes.h"
#include "Inventory.h"
#include <vector>

class Shop
{
private:
	vector<Item*> items;

public:
	Shop() 
	{
		AddItem(new RainCoat("���", 100, "���� 1�� ������.", ItemType::COAT));
		AddItem(new WetWipes("��Ƽ��", 1000, "���� 1�� �۾���.", ItemType::WIPES));
	}
	~Shop();
	void BuyItem(const ItemType& type, int& coin, Inventory& inven);
	void AddItem(Item* item);
	vector<Item*> GetItems() { return items; }
};

