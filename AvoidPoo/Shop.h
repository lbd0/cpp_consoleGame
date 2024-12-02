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
		AddItem(new RainCoat("¿ìºñ", 100, "¶ËÀ» 1¹ø ¸·¾ÆÁÜ.", ItemType::COAT));
		AddItem(new WetWipes("¹°Æ¼½´", 1000, "¶ËÀ» 1¹ø ´Û¾ÆÁÜ.", ItemType::WIPES));
	}
	~Shop();
	void BuyItem(const ItemType& type, int& coin, Inventory& inven);
	void AddItem(Item* item);
	vector<Item*> GetItems() { return items; }
};

