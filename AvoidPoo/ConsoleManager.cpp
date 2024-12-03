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

	// 키보드 입력 받아서 메뉴 선택 -> 위/아래 방향키로 이동, 스페이스바로 선택.
	do
	{
		Key key =	InputKey::Input();
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
void ConsoleManager::DrawGame(int best, double time)
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
int ConsoleManager::DrawShop(vector<Item*> items)
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

		int x = 10, y = 40;
		int index = 1;
		for (auto& item : items)
		{
			GotoXY(x, y);
			cout << index++ << ". " << item->GetName() << " 가격 : " << item->GetPrice() << "코인";
			GotoXY(x, y + 1);
			cout << "설명: " << item->GetDesc();
			x += 53;
		}

		GotoXY(35, 50);
		cout << "구매할 아이템을 선택하세요: ";
		int num;
		cin >> num;

		return num;
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

