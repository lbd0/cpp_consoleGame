#pragma once
#include "ConsoleManager.h"
#include "Poo.h"
#include "Player.h"
#include "Shop.h"
#include "RainCoat.h"
#include "WetWipes.h"
#include <vector>

class GameManager
{
private:
	ConsoleManager console;
	Poo poo;
	Player player;
	Shop shop;
public:
	void StartGame();
	void MainGame();
	void Shop();
};

