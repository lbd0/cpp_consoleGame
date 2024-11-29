#pragma once
#include <iostream>
#include "Inventory.h"
#include "Unit.h"
#include "Item.h"
using namespace std;

class Player
{
private:
	int health;
	int coin;
	Inventory inven;

public:
	Player() : health(2), coin(0) {}
	virtual ~Player() = default;
	void Move(int& x, int& y);

	int GetHealth() { return health; }
	void SetHealth(int h) { health = h; }
	int GetCoin() { return coin; }
	void SetCoin(int c) { coin = c; }
	Inventory GetInven() { return inven; }
	void UpdateInven(Inventory inven) { this->inven = inven; }

	void UseItem(const ItemType& type);
	void ShowCoin() const;
	void ShowStatus() const;
};

