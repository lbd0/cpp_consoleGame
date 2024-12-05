#include "GameManager.h"
#include <fstream>
#include <string>
#include <mmsystem.h>
#pragma comment(lib, "winmm.lib")

// ���� ������ �����ϴ� �Լ� (txt ���Ϸ� ����)
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

// ������ (����� ���� ������ ����)
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

	// ����� �κ��丮 �ҷ����� �� ����
	Inventory sInven;
	Item* it = new Item();
	for (int i = 2; i < save.size(); i += 2)
	{
		it = sInven.AddItem(stoi(save[i]));
		sInven.SetCnt(it, stoi(save[i+1]));
	}
	player->UpdateInven(sInven);

}

GameManager::~GameManager()
{
	delete player;
	player = nullptr;
}

// ���� �ٽ� �����ϸ� ���� 3���� �ʱ�ȭ
void GameManager::GameInit()
{
	player->SetHealth(3);
}

// ���� ���� �Լ�
void GameManager::StartGame()
{
	console.Init();		// �ܼ� �ʱ�ȭ
	Menu menu = console.DrawIntro();		// ����ȭ�� �׸���
	switch (menu)
	{
	// ���� ���� �޴�
	case Menu::GAME:
		GameInit();
		MainGame();
		break;
	// ���� �޴�
	case Menu::SHOP:
		Shop();
		break;
	// ���� ��� �޴�
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
	// ���� �޴�
	case Menu::QUIT:
		Save(best, player->GetCoin(), player->GetInven());
		return;
	}
}

// ���� ����
void GameManager::MainGame()
{
	// bgm ���
	//PlaySound(TEXT("bgm.wav"), 0, SND_FILENAME | SND_ASYNC | SND_LOOP);
	system("cls");
	double _time = 0;		// �ð� ���� ����
	Inventory inven = player->GetInven();		// �÷��̾� �κ��丮
	inven.ShowCnt();	// �κ��丮 ������ ���
	player->ShowHealth();		// �÷��̾� ���� ���
	player->ShowCoin();			// �÷��̾� ���� ���
	SettingPoo();	// �� ����
	SettingCoin();	// ���� ����
	int cX = 0, cY = 10;	// ���� ��� ��ġ
	int index = 0, cindex = 0;	// �� ���� �ε���, ���� ���� �ε���
	int poX = 0, poY = 10;	// �� ��� ��ġ
	bool isColl = false;		// �浹 Ȯ�� ����
	int pSpeed = 1;		// �� �������� �ӵ� ���� ����
	double speedTime = 0;		// �� �ӵ� ���� �ð� ����
	bool pMoving = false;		// ���� �������� �ִ� �� Ȯ�� ����
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

		Sleep(100);

		// �˰� �÷��̾� �浹 üũ
		if (player->IsCollision(poX+10, poY+1, Drop::POO))
		{
			// ��� �������� ����ϰ� ������, �� �¾Ƶ� Ÿ�� ����.
			if (player->GetUseItem())
			{
				console.ErasePoo(poX, poY - pSpeed);
				poY = 61;
				player->SetUseItem(false);
			}
			else
			{
				// �� �����
				console.ErasePoo(poX, poY - pSpeed);
				poY = 61;
				// �÷��̾� ���� -1
				int health = player->GetHealth();	
				health -= 1;
				player->SetHealth(health);
				player->ShowHealth();
				// �÷��̾� ��� ����
				console.ErasePlayer(player->GetX(), player->GetY());
				console.DrawPlayer(player->GetX(), player->GetY(), State::DIE);
				// �浹 �� ȿ���� ���
				Beep(392, 100);
				// �÷��̾� ������ 0 �̸� ���� ����
				if (player->GetHealth() == 0)
				{
					//PlaySound(TEXT("NULL"), 0, 0);
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
			// �÷��̾� ���� �������� ����
			int coin = player->GetCoin();
			coin += coins[index].GetPrice();
			player->SetCoin(coin);
			player->ShowCoin();
		}
		
		// �ð� ���� ��
		clock_t end = clock();
		
		// 30�� ���� ������ ���� �������� �ӵ� ����
		speedTime += (double)(end - start) / CLOCKS_PER_SEC;
		if (speedTime >= 30)
		{
			if (pMoving)
			{
				// �ӵ��� 3������ �����ϰ� �ٽ� 0����
				if (pSpeed >= 3) pSpeed = 0;
				pSpeed++;
				speedTime = 0;
			}
		}
		// ���� �÷��� �ð� ����
		_time += (double)(end - start) / CLOCKS_PER_SEC;
		// �ð� ȭ�鿡 ���
		console.DrawGame(best, (int)_time);
	} while (true);
	
}

// ���� �ý���
void GameManager::Shop()
{
	system("cls");
	// �÷��̾� �κ��丮 ���
	Inventory inven = player->GetInven();
	player->ShowCoin();
	inven.ShowInven();

	// ������ ������ ��ȣ �Է� ����.
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
	// ���� ������ �κ��丮�� ���� �� ���ο� ���� ����
	int coin = player->GetCoin();
	shop.BuyItem(type, coin, inven);
	player->UpdateInven(inven);
	player->SetCoin(coin);
	player->ShowCoin();
	Sleep(1000);
	StartGame();
}

// �������� ���� ��ġ �����ϴ� �Լ�
void GameManager::SettingPoo()
{
	poos.clear();
	vector<Poo> temp(poos);
	temp.swap(poos);
	// �������� ���� x��ǥ �������� ����
	int x, index = 0;
	do
	{
		bool isDouble = false;
		if (index == 9) break;
		x = rand() % 87;
		if (poos.empty()) poos.push_back(Poo(x, 10));
		for (int i = 0; i < poos.size(); i++)
		{
			// ���� ��ġ�� �ʰ� ����.
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

// �������� ������ ��ġ �����ϴ� �Լ�
void GameManager::SettingCoin()
{
	coins.clear();
	vector<Coin> ctemp(coins);
	ctemp.swap(coins);

	// �������� ������ x��ǥ �������� ����
	int x, index = 0;
	do
	{
		bool isDouble = false;
		if (index == 9) break;
		x = rand() % 85;
		if (coins.empty()) coins.push_back(Coin(x, 10));
		for (int i = 0; i < coins.size(); i++)
		{
			// �˰� ���ε��� ��ġ�� �ʰ� ����
			if (!poos.empty())
			{
				if (x <= poos[i].GetX() + 4 && x >= poos[i].GetX() + 5)
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


