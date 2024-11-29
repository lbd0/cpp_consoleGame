#include "ConsoleManager.h"
using namespace std;
// 콘솔창 초기화 및 커서 숨기는 함수
void ConsoleManager::Init()
{
	// 콘솔 창 크기 및 이름 설정
	system("mode con:cols=70 lines=50 | title AvoidPoo");

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
void ConsoleManager::DrawIntro()
{
	int x = 30, y = 26;		// 메뉴 선택 표시(>) 위치 변수

	system("cls");		// 콘솔 창 지우기
	GotoXY(0, 9);
	// 똥 그림 출력
	string sPoo[3] =
	{
		"000001000000000000000000000000000",
		"000011100000000000000000000000000",
		"000111110000000000000000000000000"
	};
	for (auto& sp : sPoo)
	{
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
		cout << endl;
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
		cout << endl;
	}

	// 부제 출력
	GotoXY(15, 23);
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 12);
	cout << "똥이 더러워서 피하나? 무서워서 피하지." << endl;

	// 메뉴 출력
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
	GotoXY(x-2, y);	// y = 26
	cout << "> 게임 시작" << endl;
	GotoXY(x, y+2);	// y = 28
	cout << "   상점" << endl;
	GotoXY(x, y+4); // y = 30
	cout << "게임 방법" << endl;
	GotoXY(x, y+6); // y = 32
	cout << "   종료" << endl;

	// 키보드 입력 받아서 메뉴 선택 -> 위/아래 방향키로 이동, 스페이스바로 선택.
	do
	{
		Key key =	InputKey::Input();
		if (key == Key::SPACE)
		{
			sceneManager.ChangeScene(y);
			break;
		}
		switch (key)
		{
		case Key::UP:
			if (y > 26)
			{
				GotoXY(x - 2, y);
				cout << " ";

				y -= 2;
				if (y == 28 || y == 32) x = 33;
				else x = 30;

				GotoXY(x - 2, y);
				cout << ">";
			}
			break;
		case Key::DOWN:
			if (y < 32)
			{
				GotoXY(x - 2, y);
				cout << " ";

				y += 2;
				if (y == 28 || y == 32) x = 33;
				else x = 30;

				GotoXY(x - 2, y);
				cout << ">";
			}
			break;
		}
	} while (true);

	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0);
}
