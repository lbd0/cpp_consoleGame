#include "GameManager.h"

void GameManager::GameInit()
{
	player->SetHealth(3);
}

void GameManager::StartGame()
{
	console.Init();		// 콘솔 초기화
	Menu menu = console.DrawIntro();		// 시작화면 그리기
	switch (menu)
	{
	case Menu::GAME:
		GameInit();
		MainGame();
		break;
	case Menu::SHOP:
		Shop();
		break;
	case Menu::TUTORIAL:
		console.DrawTutorial();
		do
		{
			int key = InputKey::Input();
			if (key == Key::SPACE)
			{
				StartGame();
				return;
			}
		} while (true);
		break;
	case Menu::QUIT:
		return;
	}
	// 메인화면으로 돌아가기
	
}

// 메인 게임
void GameManager::MainGame()
{
	system("cls");
	double _time = 0;
	Inventory inven = player->GetInven();
	inven.ShowCnt();
	player->ShowHealth();
	player->ShowCoin();
	srand(time(0));
	SettingPoo();
	SettingCoin();
	int cX = 0, cY = 10;
	int index = 0, cindex = 0;
	int poX = 0, poY = 10;
	bool isColl = false;
	int pSpeed = 1;
	double speedTime = 0;
	bool pMoving = false;
	do
	{
		// 시간 측정 시작
		clock_t start = clock();

		// 떨어지는 똥
		poX = poos[index].GetX();
		pMoving = poos[index].MovePoo(poX, poY, pSpeed);
		if (pMoving)
		{
			index++;
			poY = 10;
		}
		if (index == poos.size())
		{
			index = 0;
		}

		// 떨어지는 코인
		cX = coins[cindex].GetX();
		coins[cindex].MoveCoin(cX, cY);
		if (cY >= 61)
		{
			cindex++;
			cY = 10;
		}
		if (cindex == coins.size())
		{
			cindex = 0;
			SettingCoin();
		}
		// 플레이어 이동
		player->Move();	

		console.Wait(100);

		// 똥과 플레이어 충돌 체크
		if (player->IsCollision(poX+10, poY+1, Drop::POO))
		{
			if (player->GetUseItem())
			{
				console.ErasePoo(poX, poY - pSpeed);
				poY = 61;
				player->SetUseItem(false);
			}
			else
			{
				console.ErasePoo(poX, poY - pSpeed);
				poY = 61;
				int health = player->GetHealth();
				health -= 1;
				player->SetHealth(health);
				player->ShowHealth();
				console.ErasePlayer(player->GetX(), player->GetY());
				console.DrawPlayer(player->GetX(), player->GetY(), State::DIE);
				Sleep(100);
				if (player->GetHealth() == 0)
				{
					if ((int)_time > best) best = (int)_time;
					int key = console.DrawGameOver(best, (int)_time);
					if (key == Key::SPACE)
						StartGame();
					break;
				}
			}
		}

		// 코인과 플레이어 충돌 체크
		if (player->IsCollision(cX+7, cY+1, Drop::COIN))
		{
			console.EraseCoin(cX, cY - 1);
			cY = 61;
			int coin = player->GetCoin();
			coin += coins[index].GetPrice();
			player->SetCoin(coin);
			player->ShowCoin();
		}
		
		// 시간 측정 끝
		clock_t end = clock();
		
		speedTime += (double)(end - start) / CLOCKS_PER_SEC;
		if (speedTime >= 30)
		{
			if (pMoving)
			{
				if (pSpeed >= 3) pSpeed = 0;
				pSpeed++;
				speedTime = 0;
			}
		}
		_time += (double)(end - start) / CLOCKS_PER_SEC;
		
		console.DrawGame(best, (int)_time);
	} while (true);
	
}

// 상점 시스템
void GameManager::Shop()
{
	system("cls");
	console.DrawShop(shop.GetItems());
	int itemNum;
	cin >> itemNum;

	ItemType type;
	switch (itemNum)
	{
	case 0:
		StartGame();
		break;
	case 1:
		type = ItemType::COAT;
		break;
	case 2:
		type = ItemType::WIPES;
		break;
	default :
		cout << "존재하지 않는 아이템입니다.";
		Sleep(1000);
		StartGame();
		return;
	}
	int coin = player->GetCoin();
	Inventory inven = player->GetInven();
	shop.BuyItem(type, coin, inven);
	player->UpdateInven(inven);
	player->SetCoin(coin);
	Sleep(1000);
	StartGame();
}

void GameManager::SettingPoo()
{
	poos.clear();
	vector<Poo> temp(poos);
	temp.swap(poos);
	int x, index = 0;
	do
	{
		bool isDouble = false;
		if (index == 9) break;
		x = rand() % 87;
		if (poos.empty()) poos.push_back(Poo(x, 10));
		for (int i = 0; i < poos.size(); i++)
		{
			if (x <= poos[i].GetX()+3 && x >= poos[i].GetX()-3)
			{
				isDouble = true;
				break;
			}
		}
		if (!isDouble)
		{
			poos.push_back(Poo(x, 10));
			index++;
		}


	} while (true);
}

void GameManager::SettingCoin()
{
	coins.clear();
	vector<Coin> ctemp(coins);
	ctemp.swap(coins);

	int x, index = 0;
	do
	{
		bool isDouble = false;
		if (index == 9) break;
		x = rand() % 85;
		if (coins.empty()) coins.push_back(Coin(x, 10));
		for (int i = 0; i < coins.size(); i++)
		{
			if (!poos.empty())
			{
				if (x <= poos[i].GetX() + 3 && x >= poos[i].GetX() - 3)
				{
					break;
				}
			}
			if (x <= coins[i].GetX() + 3 && x >= coins[i].GetX() - 3)
			{
				isDouble = true;
				break;
			}
		}
		if (!isDouble)
		{
			coins.push_back(Coin(x, 10));
			index++;
		}
	} while (true);
}


