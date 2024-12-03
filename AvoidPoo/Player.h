#pragma once
#include <iostream>
#include "Inventory.h"
#include "Unit.h"
#include "Item.h"
#include "ConsoleManager.h"
using namespace std;

class Player
{
private:
	int x;
	int y;
	int health;
	int coin;
	bool isColl = false;
	bool useItem = false;
	Inventory inven;
	ConsoleManager console;
public:
	Player(int x, int y) : health(3), coin(1000), x(x), y(y) {}
	virtual ~Player() = default;
	void Move();
	bool IsCollision(int cx, int cy, Drop drop);
	int GetHealth() { return health; }
	void SetHealth(int h) { health = h; }
	int GetCoin() { return coin; }
	void SetCoin(int c) { coin = c; }
	Inventory GetInven() { return inven; }
	void UpdateInven(Inventory inven) { this->inven = inven; }
	int GetX() { return x; }
	int GetY() { return y; }
	bool GetUseItem() { return useItem; }
	void SetUseItem(bool u) { useItem = u; }

	void UseItem(const ItemType& type);
	void ShowCoin();
	void ShowStatus() const;
	void ShowHealth();
};

