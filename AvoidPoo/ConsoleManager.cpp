#include "ConsoleManager.h"
using namespace std;
// 콘솔창 초기화 및 커서 숨기는 함수
void ConsoleManager::Init()
{
	// 콘솔 창 크기 및 이름 설정
	system("mode con:cols=100 lines=63 | title AvoidPoo");

	// 커서 숨기기
	HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_CURSOR_INFO ConsoleCursor;
	ConsoleCursor.bVisible = 0;
	ConsoleCursor.dwSize = 1;
	SetConsoleCursorInfo(consoleHandle, &ConsoleCursor);
}

// 커서 위치 이동 함수
void ConsoleManager::GotoXY(const int& x, const int& y)
{
	HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);		// 콘솔 핸들 가져오기
	COORD pos;
	pos.X = x;
	pos.Y = y;
	SetConsoleCursorPosition(consoleHandle, pos);
}

// 시작화면 그리는 함수
Menu ConsoleManager::DrawIntro()
{
	int x = 46, y = 32;		// 메뉴 선택 표시(>) 위치 변수

	system("cls");		// 콘솔 창 지우기
	int tX = 15, tY = 15;
	
	// 똥 그림 출력
	string sPoo[3] =
	{
		"000001000",
		"000011100",
		"000111110"
	};
	for (auto& sp : sPoo)
	{
		GotoXY(tX, tY++);
		for (auto& s : sp)
		{
			if (s == '0')
			{
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0);		// 글씨 색상 변경
				cout << "□";
			}
			else
			{
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 6);
				cout << "■";
			}
		}
	}
	// 똥피하기 출력
	string sAvoid[10] =
	{	"000000000000000010000000100000010",
		"000111110000000010001000100000010",
		"000101000011111010111110101111010",
		"000111110001010010000000100001010",
		"000001000001010010001000111001010",
		"001111111001010010010100100001010",
		"000011100011111010010100100001010",
		"000100010000000010001000100001010",
		"000100010000000010000000100001010",
		"000011100000000010000000100000010"
	};
	for (auto& av : sAvoid)
	{
		GotoXY(tX, tY++);
		for (auto& a : av)
		{
			if (a == '0')
			{
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0);
				cout << "□";
			}
			else
			{
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 4);
				cout << "■";
			}
		}
	}

	// 부제 출력
	GotoXY(33, 29);
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 12);
	cout << "똥이 더러워서 피하나? 무서워서 피하지." << endl;

	// 메뉴 출력
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
	GotoXY(x-2, y);	// y = 32
	cout << "> 게임 시작" << endl;
	GotoXY(x, y+2);	// y = 34
	cout << "   상점" << endl;
	GotoXY(x, y+4); // y = 36
	cout << "게임 방법" << endl;
	GotoXY(x, y+6); // y = 38
	cout << "   종료" << endl;

	GotoXY(10, 50);
	cout << "이동 : ↑/↓, 선택 : space";

	// 키보드 입력 받아서 메뉴 선택 -> 위/아래 방향키로 이동, 스페이스바로 선택.
	do
	{
		int key =	InputKey::Input();
		if (key == Key::SPACE)
		{
			return ChangeScene(y);
		}
		switch (key)
		{
		case Key::UP:
			if (y > 32)
			{
				GotoXY(x - 2, y);
				cout << " ";

				y -= 2;
				if (y == 34 || y == 38) x = 49;
				else x = 46;

				GotoXY(x - 2, y);
				cout << ">";
			}
			break;
		case Key::DOWN:
			if (y < 38)
			{
				GotoXY(x - 2, y);
				cout << " ";

				y += 2;
				if (y == 34 || y == 38) x = 49;
				else x = 46;

				GotoXY(x - 2, y);
				cout << ">";
			}
			break;
		}
	} while (true);

	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0);
}

// 게임 화면 그리는 함수
void ConsoleManager::DrawGame(int best, int time)
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
	// 시간 및 기록
	GotoXY(2, 2);
	cout << "최고 기록 : " << best << "초";

	GotoXY(2, 6);
	cout << time << "초";

}

// 똥 그리기 함수
void ConsoleManager::DrawPoo(int x, int y)
{
	string poo[3] =
	{
		{"0001000"},
		{"0011100"},
		{"0111110"}
	};
	for (auto& po : poo)
	{
		GotoXY(x, y++);
		for (auto& p : po)
		{
			if (p == '0')
			{
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0);		// 글씨 색상 변경
				cout << "□";
			}
			else
			{
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 6);
				cout << "■";
			}
		}
	}
}

// 똥 지우는 함수
void ConsoleManager::ErasePoo(int x, int y)
{
	for (int i = 0; i < 3; i++)
	{
		GotoXY(x, y++);
		for (int j = 0; j < 7; j++)
		{
			cout << "  ";
		}
	}
}

// 생명 (하트) 그리는 함수
void ConsoleManager::DrawHealth(int x, int y)
{
	string health[4] =
	{
		{"01010"},
		{"11111"},
		{"01110"},
		{"00100"}
	};
	for (auto& he : health)
	{
		GotoXY(x, y++);
		for (auto& h : he)
		{
			if (h == '0')
			{
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0);		// 글씨 색상 변경
				cout << "□";
			}
			else
			{
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 12);
				cout << "■";
			}
		}
	}
}

// 빈하트 그리는 함수
void ConsoleManager::DrawDeath(int x, int y)
{
	string health[4] =
	{
		{"01010"},
		{"11111"},
		{"01110"},
		{"00100"}
	};
	for (auto& he : health)
	{
		GotoXY(x, y++);
		for (auto& h : he)
		{
			if (h == '0')
			{
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0);		// 글씨 색상 변경
				cout << "□";
			}
			else
			{
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 12);
				cout << "□";
			}
		}
	}
}

// 물티슈 아이템 그리는 함수
void ConsoleManager::DrawWipe(int x, int y)
{
	string wipe[10] =
	{
		{"0011110000111100"},
		{"0111111001111110"},
		{"1111111111111111"},
		{"0111111111111110"},
		{"0011111111111100"},
		{"0001111111111000"},
		{"0000111111110000"},
		{"0000011111100000"},
		{"0000001111000000"},
		{"0000000110000000"},
	};

	for (auto& wi : wipe)
	{
		GotoXY(x, y++);
		for (auto& w : wi)
		{
			if (w == '0')
			{
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0);		// 글씨 색상 변경
				cout << "□";
			}
			else
			{
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 12);
				cout << "■";
			}
		}
	}
}



// 플레이어 그리는 함수
void ConsoleManager::DrawPlayer(int x, int y, State state)
{
	int idel_player[15][17] =
	{
		{0,3,3,0,0,0,0,0,0,0,0,0,0,0,3,3,0},
		{3,0,0,3,0,0,0,0,0,0,0,0,0,3,0,0,3},
		{3,0,0,0,3,0,0,3,3,3,0,0,3,0,0,0,3},
		{3,0,0,0,0,3,3,0,0,0,3,3,0,0,0,0,3},
		{0,3,0,0,0,0,0,0,0,0,0,0,0,0,0,3,0},
		{0,3,0,0,0,0,0,0,0,0,0,0,0,0,0,3,0},
		{3,0,1,1,1,1,0,0,0,0,0,1,1,1,1,0,3},
		{3,0,1,0,0,0,1,0,0,0,1,0,0,0,1,0,3},
		{3,0,1,1,1,1,1,1,0,1,1,1,1,1,1,0,3},
		{3,0,0,1,0,0,0,1,0,1,0,0,0,1,0,0,3},
		{0,3,0,0,1,1,1,0,0,0,1,1,1,0,0,3,0},
		{0,3,0,0,0,0,0,0,0,0,0,0,0,0,0,3,0},
		{0,0,3,3,0,0,0,0,1,0,0,0,0,3,3,0,0},
		{0,0,0,0,3,3,3,0,0,0,3,3,3,0,0,0,0},
		{0,0,0,0,0,0,0,3,3,3,0,0,0,0,0,0,0}
	};

	int move_player[15][17] =
	{
		{0,3,3,0,0,0,0,0,0,0,0,0,0,0,3,3,0},
		{3,0,0,3,0,0,0,0,0,0,0,0,0,3,0,0,3},
		{3,0,0,0,3,0,0,3,3,3,0,0,3,0,0,0,3},
		{3,0,0,0,0,3,3,0,0,0,3,3,0,0,0,0,3},
		{0,3,0,0,0,0,0,0,0,0,0,0,0,0,0,3,0},
		{0,3,0,0,0,0,0,0,0,0,0,0,0,0,0,3,0},
		{3,0,1,1,1,1,0,0,0,0,0,1,1,1,1,0,3},
		{3,0,1,2,2,1,1,0,0,0,1,1,2,2,1,0,3},
		{3,0,1,2,2,1,2,1,0,1,2,1,2,2,1,0,3},
		{3,0,0,1,2,1,2,1,0,1,2,1,2,1,0,0,3},
		{0,3,0,0,1,1,1,0,0,0,1,1,1,0,0,3,0},
		{0,3,0,0,0,0,0,0,0,0,0,0,0,0,0,3,0},
		{0,0,3,3,0,0,0,0,1,0,0,0,0,3,3,0,0},
		{0,0,0,0,3,3,3,0,0,0,3,3,3,0,0,0,0},
		{0,0,0,0,0,0,0,3,3,3,0,0,0,0,0,0,0}
	};

	int die_player[15][17] =
	{
		{0,1,1,0,0,0,0,0,0,0,0,0,0,0,1,1,0},
		{1,0,0,1,0,0,0,0,0,0,0,0,0,1,0,0,1},
		{1,0,0,0,1,0,0,1,1,1,0,0,1,0,0,0,1},
		{1,0,0,0,0,1,1,0,0,0,1,1,0,0,0,0,1},
		{0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0},
		{0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0},
		{1,0,2,2,2,2,0,0,0,0,0,2,2,2,2,0,1},
		{1,0,2,2,2,2,2,0,0,0,2,2,2,2,2,0,1},
		{1,0,2,2,2,2,2,2,0,2,2,2,2,2,2,0,1},
		{1,0,0,2,2,2,2,2,0,2,2,2,2,2,0,0,1},
		{0,1,0,0,2,2,2,0,0,0,2,2,2,0,0,1,0},
		{0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0},
		{0,0,1,1,0,0,0,0,1,0,0,0,0,1,1,0,0},
		{0,0,0,0,1,1,1,0,0,0,1,1,1,0,0,0,0},
		{0,0,0,0,0,0,0,1,1,1,0,0,0,0,0,0,0}
	};
	switch(state)
	{
	case State::IDEL:
		for (auto& pl : idel_player)
		{
			GotoXY(x, y++);
			for (auto& p : pl)
			{
				switch (p)
				{
				case 0 :
					SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0);		// 글씨 색상 변경
					cout << "□";
					break;
				case 1:
					SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
					cout << "■";
					break;
				case 3:
					SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
					cout << "■";
					break;
				}
			}
		}
		break;
	case State::MOVE:
		for (auto& pl : move_player)
		{
			GotoXY(x, y++);
			for (auto& p : pl)
			{
				switch (p)
				{
				case 0:
					SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0);		// 글씨 색상 변경
					cout << "□";
					break;
				case 1:
					SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
					cout << "■";
					break;
				case 3: 
					SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
					cout << "■";
					break;
				case 2:
					SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 14);
					cout << "■";
					break;
				}
			}
		}
		break;
	case State::DIE:
		for (auto& pl : die_player)
		{
			GotoXY(x, y++);
			for (auto& p : pl)
			{
				if (p == 0)
				{
					SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0);		// 글씨 색상 변경
					cout << "□";
				}
				else if(p ==1)
				{
					SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),15);
					cout << "■";
				}
				else
				{
					SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 4);
					cout << "■";
				}
			}
		}
		break;
	case State::RAINCOAT_IDEL:
		for (auto& pl : idel_player)
		{
			GotoXY(x, y++);
			for (auto& p : pl)
			{
				switch (p)
				{
				case 0 :
					SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0);		// 글씨 색상 변경
					cout << "□";
					break;
				case 1 :
					SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
					cout << "■";
					break;
				case 3:
					SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 9);
					cout << "■";
					break;
				}
			}
		}
		break;
	case State::RAINCOAT_MOVE:
		for (auto& pl : move_player)
		{
			GotoXY(x, y++);
			for (auto& p : pl)
			{
				switch (p)
				{
				case 0 :
					SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0);		// 글씨 색상 변경
					cout << "□";
					break;
				case 1:
					SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
					cout << "■";
					break;
				case 2:
					SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 14);
					cout << "■";
					break;
				case 3:
					SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 9);
					cout << "■";
					break;
				}
			}
		}
		break;
	}
}

// 플레이어 지우는 함수
void ConsoleManager::ErasePlayer(int x, int y)
{
	for (int i=0; i<15; i++)
	{
		GotoXY(x, y++);
		for (int j =0; j<17 ;j++)
		{
			cout << "  ";
		}
	}
}

// 상점 그리는 함수
void ConsoleManager::DrawShop(vector<Item*> items)
{
		
		GotoXY(35, 5);
		cout << "  ■    ■    ■■■  ■";
		GotoXY(35, 6);
		cout << "■  ■  ■■    ■  ■■";
		GotoXY(35, 7);
		cout << "        ■    ■  ■  ■";
		GotoXY(35, 8);
		cout << "      ■          ■■■";
		GotoXY(35, 9);
		cout << "    ■  ■        ■  ■";
		GotoXY(35, 10);
		cout << "      ■          ■■■";


		int tx = 13, ty = 40;
		int index = 1;
		for (auto& item : items)
		{
			GotoXY(tx, ty);
			cout << index++ << ". " << item->GetName() << " (" << item->GetPrice() << "코인)";
			GotoXY(tx, ty + 2);
			cout << "설명: " << item->GetDesc();
			tx += 50;
		}
		int rainX = 7, rainY = 20;
		DrawPlayer(rainX, rainY, State::RAINCOAT_IDEL);

		int wipeX = 60, wipeY = 25;
		DrawWipe(wipeX, wipeY);

		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
		GotoXY(43, 48);
		cout << "0. 돌아가기";
		GotoXY(35, 50);
		cout << "구매할 아이템을 선택하세요: ";

}

// 코인 그리는 함수
void ConsoleManager::DrawCoin(int x, int y)
{
	string coin[4] =
	{
		{"0110"},
		{"1001"},
		{"1001"},
		{"0110"}
	};
	for (auto& co : coin)
	{
		GotoXY(x, y++);
		for (auto& c : co)
		{
			if (c == '0')
			{
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0);		// 글씨 색상 변경
				cout << "□";
			}
			else
			{
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 14);
				cout << "■";
			}
		}
	}
}

// 코인 지우는 함수
void ConsoleManager::EraseCoin(int x, int y)
{
	for (int i = 0; i < 4; i++)
	{
		GotoXY(x, y++);
		for (int j = 0; j < 4; j++)
		{
			cout << "  ";
		}
	}
}

// 게임방법 타이틀 그리는 함수
void ConsoleManager::DrawTutorialTitle(int x, int y)
{
	string title[10] =
	{
		{"000001010000000100000001000000001"},
		{"000001010001100100100101000100101"},
		{"111101010010010100100101000100101"},
		{"000101010010010100111101100111111"},
		{"000111010010010100100101000100101"},
		{"000101010001100100111101000111101"},
		{"000101010000000100000110000001001"},
		{"000101010000111100001001000001111"},
		{"000001010000100100001001000001001"},
		{"000001010000111100000110000001111"},
	};

	for (auto& ti : title)
	{
		GotoXY(x, y++);
		for (auto& t : ti)
		{
			if (t == '0')
			{
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0);		// 글씨 색상 변경
				cout << "□";
			}
			else
			{
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 6);
				cout << "■";
			}
		}
	}

} 

// 게임 방법 그리는 함수
void ConsoleManager::DrawTutorial()
{
	system("cls");
	DrawTutorialTitle(15, 3);
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
	GotoXY(15, 15);
	cout << "1. 플레이어는 좌우 방향키를 이용하여 좌우로 움직일 수 있습니다.";
	GotoXY(15, 17);
	cout << "2. 똥을 3번 맞으면 GameOver!";
	GotoXY(15, 19);
	cout << "3. 코인을 맞으면 코인을 얻을 수 있습니다. (금액은 랜덤!)";
	GotoXY(15, 21);
	cout << "4. 최대한 오랜 시간 똥을 피해 버텨보세요.";
	GotoXY(15, 24);
	cout << "---------------------아이템---------------------";
	GotoXY(15, 26);
	cout << "1. 우비 (100 코인) : 똥을 단 한 번 막아줍니다.";
	GotoXY(15, 28);
	cout << "2. 물티슈 (1000 코인) : 똥을 한 번 닦아줍니다. (생명 +1)";
	GotoXY(15, 30);
	cout << "---------------------조작법---------------------";
	GotoXY(15, 32);
	cout << "1. 시작 화면";
	GotoXY(15, 34);
	cout << "상하 방향키를 이용하여 이동, 스페이스바를 이용하여 선택할 수 있습니다.";
	GotoXY(15, 36);
	cout << "2. 상점";
	GotoXY(15, 38);
	cout << "아이템의 번호를 입력하여 아이템 구매할 수 있습니다. (1 : 우비, 2 : 물티슈)";
	GotoXY(15, 40);
	cout << "상점 1회 이용 시 자동으로 시작 화면으로 이동합니다.";
	GotoXY(15, 42);
	cout << "3. 게임";
	GotoXY(15, 44);
	cout << "좌우 방향키를 이용하여 플레이어를 제어합니다.";
	GotoXY(15, 46);
	cout << "게임 오버 시 스페이스바를 이용하여 시작화면으로 이동할 수 있습니다.";

	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 6);
	GotoXY(40, 50);
	cout << "> 돌아가기 (space)";

}

// 게임 오버 그리는 함수
int ConsoleManager::DrawGameOver(int best, int time)
{
	int x = 15, y = 17;
	string gameOver[10] =
	{
		{"0000010100000001000000000000000001"},
		{"0000010100011001000011100001000101"},
		{"1111010100100101000100010001000101"},
		{"0001010100100101000100010001000101"},
		{"0001110100100101000100010001111111"},
		{"0001010100011001000011100001000101"},
		{"0001010100000001000001000001000101"},
		{"0001010100001111000001000001111101"},
		{"0000010100001001001111111000000001"},
		{"0000010100001111000000000000000001"}
	};

	for (auto& ga : gameOver)
	{
		GotoXY(x, y++);
		for (auto& g : ga)
		{
			if (g == '0')
			{
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0);		// 글씨 색상 변경
				cout << "□";
			}
			else
			{
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 4);
				cout << "■";
			}
		}
	}

	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
	GotoXY(33, 30);
	cout << "기록 : " << time << "초";
	GotoXY(55, 30);
	cout << "최고 기록 : " << best << "초";

	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
	GotoXY(43, 35);
	cout << "> 돌아가기 (space)";

	do
	{
		if (_kbhit())
		{
			int key = InputKey::Input();
			if (key == Key::SPACE)
			{
				return key;
			}
		}
	} while (true);
}

void ConsoleManager::Wait(DWORD dwMillisecond)
{
	MSG msg;
	DWORD dwStart;
	dwStart = GetTickCount();

	while (GetTickCount() - dwStart < dwMillisecond)
	{
		while (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
	}
}




// 화면 변경하는 함수
Menu ConsoleManager::ChangeScene(int n)
{
	switch (n)
	{
	case Menu::GAME:
		return Menu::GAME;
	case Menu::SHOP:
		return Menu::SHOP;
	case Menu::TUTORIAL:
		return  Menu::TUTORIAL;
	case Menu::QUIT:
		return Menu::QUIT;
	}
}

