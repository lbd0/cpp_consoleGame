#include "GameManager.h"

void GameManager::StartGame()
{
	console.Init();		// �ܼ� �ʱ�ȭ
	Menu menu = console.DrawIntro();		// ����ȭ�� �׸���
	switch (menu)
	{
	case Menu::GAME:
		MainGame();
		break;
	case Menu::SHOP:
		Shop();
		break;
	case Menu::TUTORIAL:
		break;
	case Menu::QUIT:
		return;
	}
}

// ���� ����
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
	do
	{
		clock_t start = clock();

		// �������� ��
		poX = poos[index].GetX();
		poos[index].MovePoo(poX, poY);
		if (poY > 61)
		{
			index++;
			poY = 10;
		}
		if (index == poos.size())
		{
			index = 0;
		}

		// �������� ����
		cX = coins[cindex].GetX();
		coins[cindex].MoveCoin(cX, cY);
		if (cY > 61)
		{
			cindex++;
			cY = 10;
		}
		if (cindex == coins.size())
		{
			cindex = 0;
		}

		// �÷��̾� �̵�
		player->Move();	
		Sleep(100);

		// �˰� �÷��̾� �浹 üũ
		if (player->IsCollision(poX+10, poY+1, Drop::POO))
		{
			if (player->GetUseItem())
			{
				console.ErasePoo(poX, poY - 1);
				poY = 61;
				player->SetUseItem(false);
			}
			else
			{
				console.ErasePoo(poX, poY - 1);
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
					break;
				}
			}
			
		}


		// ���ΰ� �÷��̾� �浹 üũ
		if (player->IsCollision(cX+7, cY+1, Drop::COIN))
		{
			console.EraseCoin(cX, cY - 1);
			cY = 61;
			int coin = player->GetCoin();
			coin += 1;
			player->SetCoin(coin);
			player->ShowCoin();
		}
		
		clock_t end = clock();
		
		_time += (double)(end - start) / CLOCKS_PER_SEC;
		console.DrawGame(0, (int)_time);

	} while (true);
	
}

// ���� �ý���
void GameManager::Shop()
{
	system("cls");
	int itemNum = console.DrawShop(shop.GetItems());
	ItemType type;
	switch (itemNum)
	{
	case 1:
		type = ItemType::COAT;
		break;
	case 2:
		type = ItemType::WIPES;
		break;
	default :
		cout << "�������� �ʴ� �������Դϴ�.";
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
	int x, index = 0;
	do
	{
		bool isDouble = false;
		if (index == 9) break;
		x = rand() % 87;
		if (coins.empty()) coins.push_back(Coin(x, 10));
		for (int i = 0; i < coins.size(); i++)
		{
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


