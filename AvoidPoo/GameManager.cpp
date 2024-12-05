#include "GameManager.h"
#include <fstream>
#include <string>

void Save(int best, int coin, Inventory inven)
{
	ofstream fout;

	fout.open("save.txt");

	fout << best << endl;
	fout << coin << endl;

	map<Item*, int> sInven = inven.GetItem();
	
	for (auto& save : sInven)
	{
		Item* sItem = save.first;
		int type = sItem->GetType();
		fout << type << endl;
		fout << save.second << endl;
	}

	fout.close();
}

GameManager::GameManager()
{
	// ����� �ְ���, ���� �ҷ����� 
	int b = 0, c = 0;

	ifstream ifs;

	ifs.open("save.txt");

	if (!ifs) return;

	string line;
	vector<string> save;
	while (getline(ifs, line))
	{
		save.push_back(line);
	}
	ifs.close();

	// ����� �ְ���, ���� ���� 
	b = stoi(save[0]);
	c = stoi(save[1]);
	best = b;
	player->SetCoin(c);

	// ����� �κ��丮 �ҷ�����
	Inventory sInven;
	Item* it = new Item();
	for (int i = 2; i < save.size(); i += 2)
	{
		it = sInven.AddItem(stoi(save[i]));
		sInven.SetCnt(it, stoi(save[i+1]));
	}
	player->UpdateInven(sInven);

}

void GameManager::GameInit()
{
	player->SetHealth(3);
}

void GameManager::StartGame()
{
	console.Init();		// �ܼ� �ʱ�ȭ
	Menu menu = console.DrawIntro();		// ����ȭ�� �׸���
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
		// ����ȭ������ ���ư���
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
		Save(best, player->GetCoin(), player->GetInven());
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
	int pSpeed = 1;
	double speedTime = 0;
	bool pMoving = false;
	do
	{
		// �ð� ���� ����
		clock_t start = clock();

		// �������� ��
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

		// �������� ����
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
		// �÷��̾� �̵�
		player->Move();	

		console.Wait(100);

		// �˰� �÷��̾� �浹 üũ
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

		// ���ΰ� �÷��̾� �浹 üũ
		if (player->IsCollision(cX+7, cY+1, Drop::COIN))
		{
			console.EraseCoin(cX, cY - 1);
			cY = 61;
			int coin = player->GetCoin();
			coin += coins[index].GetPrice();
			player->SetCoin(coin);
			player->ShowCoin();
		}
		
		// �ð� ���� ��
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

// ���� �ý���
void GameManager::Shop()
{
	system("cls");
	Inventory inven = player->GetInven();
	player->ShowCoin();
	inven.ShowInven();
	console.DrawShop(shop.GetItems());
	int itemNum;
	cin >> itemNum;

	ItemType type;
	switch (itemNum)
	{
	case 0:
		StartGame();
		return;
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
	shop.BuyItem(type, coin, inven);
	player->UpdateInven(inven);
	player->SetCoin(coin);
	player->ShowCoin();
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


