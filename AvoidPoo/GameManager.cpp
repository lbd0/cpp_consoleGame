#include "GameManager.h"
#include <fstream>
#include <string>
#include <mmsystem.h>
#pragma comment(lib, "winmm.lib")

// 게임 데이터 저장하는 함수 (txt 파일로 저장)
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

// 생성자 (저장된 게임 데이터 적용)
GameManager::GameManager()
{
	// 저장된 최고기록, 코인 불러오기 
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

	// 저장된 최고기록, 코인 적용
	b = stoi(save[0]);
	c = stoi(save[1]);
	best = b;
	player->SetCoin(c);

	// 저장된 인벤토리 불러오기 및 적용
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

// 게임 다시 시작하면 생명 3으로 초기화
void GameManager::GameInit()
{
	player->SetHealth(3);
}

// 게임 시작 함수
void GameManager::StartGame()
{
	console.Init();		// 콘솔 초기화
	Menu menu = console.DrawIntro();		// 시작화면 그리기
	switch (menu)
	{
	// 게임 시작 메뉴
	case Menu::GAME:
		GameInit();
		MainGame();
		break;
	// 상점 메뉴
	case Menu::SHOP:
		Shop();
		break;
	// 게임 방법 메뉴
	case Menu::TUTORIAL:
		console.DrawTutorial();
		// 메인화면으로 돌아가기
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
	// 종료 메누
	case Menu::QUIT:
		Save(best, player->GetCoin(), player->GetInven());
		return;
	}
}

// 메인 게임
void GameManager::MainGame()
{
	// bgm 재생
	//PlaySound(TEXT("bgm.wav"), 0, SND_FILENAME | SND_ASYNC | SND_LOOP);
	system("cls");
	double _time = 0;		// 시간 측정 변수
	Inventory inven = player->GetInven();		// 플레이어 인벤토리
	inven.ShowCnt();	// 인벤토리 아이템 출력
	player->ShowHealth();		// 플레이어 생명 출력
	player->ShowCoin();			// 플레이어 코인 출력
	SettingPoo();	// 똥 세팅
	SettingCoin();	// 코인 세팅
	int cX = 0, cY = 10;	// 코인 출력 위치
	int index = 0, cindex = 0;	// 똥 벡터 인덱스, 코인 벡터 인덱스
	int poX = 0, poY = 10;	// 똥 출력 위치
	bool isColl = false;		// 충돌 확인 변수
	int pSpeed = 1;		// 똥 떨어지는 속도 제어 변수
	double speedTime = 0;		// 똥 속도 제어 시간 변수
	bool pMoving = false;		// 똥이 떨어지고 있는 지 확인 변수
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

		Sleep(100);

		// 똥과 플레이어 충돌 체크
		if (player->IsCollision(poX+10, poY+1, Drop::POO))
		{
			// 우비 아이템을 사용하고 있으면, 똥 맞아도 타격 없음.
			if (player->GetUseItem())
			{
				console.ErasePoo(poX, poY - pSpeed);
				poY = 61;
				player->SetUseItem(false);
			}
			else
			{
				// 똥 지우고
				console.ErasePoo(poX, poY - pSpeed);
				poY = 61;
				// 플레이어 생명 -1
				int health = player->GetHealth();	
				health -= 1;
				player->SetHealth(health);
				player->ShowHealth();
				// 플레이어 모양 변경
				console.ErasePlayer(player->GetX(), player->GetY());
				console.DrawPlayer(player->GetX(), player->GetY(), State::DIE);
				// 충돌 시 효과음 재생
				Beep(392, 100);
				// 플레이어 생명이 0 이면 게임 오버
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

		// 코인과 플레이어 충돌 체크
		if (player->IsCollision(cX+7, cY+1, Drop::COIN))
		{
			console.EraseCoin(cX, cY - 1);
			cY = 61;
			// 플레이어 코인 랜덤으로 증가
			int coin = player->GetCoin();
			coin += coins[index].GetPrice();
			player->SetCoin(coin);
			player->ShowCoin();
		}
		
		// 시간 측정 끝
		clock_t end = clock();
		
		// 30초 지날 때마다 똥의 떨어지는 속도 증가
		speedTime += (double)(end - start) / CLOCKS_PER_SEC;
		if (speedTime >= 30)
		{
			if (pMoving)
			{
				// 속도는 3까지만 증가하고 다시 0으로
				if (pSpeed >= 3) pSpeed = 0;
				pSpeed++;
				speedTime = 0;
			}
		}
		// 게임 플레이 시간 측정
		_time += (double)(end - start) / CLOCKS_PER_SEC;
		// 시간 화면에 출력
		console.DrawGame(best, (int)_time);
	} while (true);
	
}

// 상점 시스템
void GameManager::Shop()
{
	system("cls");
	// 플레이어 인벤토리 출력
	Inventory inven = player->GetInven();
	player->ShowCoin();
	inven.ShowInven();

	// 구매할 아이템 번호 입력 받음.
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
		cout << "존재하지 않는 아이템입니다.";
		Sleep(1000);
		StartGame();
		return;
	}
	// 구매 아이템 인벤토리에 적용 및 코인에 변동 적용
	int coin = player->GetCoin();
	shop.BuyItem(type, coin, inven);
	player->UpdateInven(inven);
	player->SetCoin(coin);
	player->ShowCoin();
	Sleep(1000);
	StartGame();
}

// 떨어지는 똥의 위치 세팅하는 함수
void GameManager::SettingPoo()
{
	poos.clear();
	vector<Poo> temp(poos);
	temp.swap(poos);
	// 떨어지는 똥의 x좌표 랜덤으로 지정
	int x, index = 0;
	do
	{
		bool isDouble = false;
		if (index == 9) break;
		x = rand() % 87;
		if (poos.empty()) poos.push_back(Poo(x, 10));
		for (int i = 0; i < poos.size(); i++)
		{
			// 똥이 겹치지 않게 조절.
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

// 떨어지는 코인의 위치 세팅하는 함수
void GameManager::SettingCoin()
{
	coins.clear();
	vector<Coin> ctemp(coins);
	ctemp.swap(coins);

	// 떨어지는 코인의 x좌표 랜덤으로 지정
	int x, index = 0;
	do
	{
		bool isDouble = false;
		if (index == 9) break;
		x = rand() % 85;
		if (coins.empty()) coins.push_back(Coin(x, 10));
		for (int i = 0; i < coins.size(); i++)
		{
			// 똥과 코인들이 겹치지 않게 조절
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


