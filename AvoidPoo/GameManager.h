#pragma once
#include "ConsoleManager.h"
#include "Poo.h"
#include "Coin.h"
#include "Player.h"
#include "Shop.h"
#include "RainCoat.h"
#include "WetWipes.h"
#include <vector>
#include <time.h>

class GameManager
{
private:
	ConsoleManager console;
	vector<Poo> poos;
	vector<Coin> coins;
	Player* player = new Player(0, 45);
	Shop shop;
	int best = 0;
public:
	GameManager() {}
	void GameInit();
	void StartGame();
	void MainGame();
	void Shop();
	void SettingPoo();
	void SettingCoin();
};

