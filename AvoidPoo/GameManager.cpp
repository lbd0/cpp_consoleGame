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
	Inventory inven = player.GetInven();
	console.DrawGame(0, 0);
	inven.ShowCnt();
	player.ShowHealth();
	srand(time(0));
	// ���� ���� �ؾ��� �ѤѤѤѤ�
	// �������� �� �����ǰ� �������°�
	// �浹üũ -> ���� ��� ��
	// ������ ���
	// ���ε� ������ �ϳ�?
	int pX = 0, pY = 45;
	int poX = rand() % 88, poY = 10;
	vector<int> pooPos;
	int cX = 0, cY = 30;
	do
	{
		console.DrawCoin(cX, cY);	// ����
		player.Move(pX, pY);	// �÷��̾� �̵�
		poo.MovePoo(poX, poY);	// �� �̵�
		Sleep(100);
	} while (true);
}

// ���� �ý���
void GameManager::Shop()
{
	system("cls");
	console.GotoXY(0, 0);
	player.ShowCoin();
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
	int coin = player.GetCoin();
	Inventory inven = player.GetInven();
	shop.BuyItem(type, coin, inven);
	player.UpdateInven(inven);
	player.SetCoin(coin);
	Sleep(1000);
	StartGame();
}


