#include "GameManager.h"

void GameManager::StartGame()
{
	console.Init();		// 콘솔 초기화
	Menu menu = console.DrawIntro();		// 시작화면 그리기
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

// 메인 게임
void GameManager::MainGame()
{
	Inventory inven = player.GetInven();
	console.DrawGame(0, 0);
	inven.ShowCnt();
	player.ShowHealth();
	srand(time(0));
	// 게임 구현 해야해 ㅡㅡㅡㅡㅡ
	// 랜덤으로 똥 생성되고 떨어지는거
	// 충돌체크 -> 생명 닳는 거
	// 아이템 사용
	// 코인도 만들어야 하네?
	int pX = 0, pY = 45;
	int poX = rand() % 88, poY = 10;
	vector<int> pooPos;
	int cX = 0, cY = 30;
	do
	{
		console.DrawCoin(cX, cY);	// 코인
		player.Move(pX, pY);	// 플레이어 이동
		poo.MovePoo(poX, poY);	// 똥 이동
		Sleep(100);
	} while (true);
}

// 상점 시스템
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
		cout << "존재하지 않는 아이템입니다.";
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


