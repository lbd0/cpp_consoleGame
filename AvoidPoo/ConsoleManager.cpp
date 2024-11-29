#include "ConsoleManager.h"
using namespace std;
// �ܼ�â �ʱ�ȭ �� Ŀ�� ����� �Լ�
void ConsoleManager::Init()
{
	// �ܼ� â ũ�� �� �̸� ����
	system("mode con:cols=70 lines=50 | title AvoidPoo");

	// Ŀ�� �����
	HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_CURSOR_INFO ConsoleCursor;
	ConsoleCursor.bVisible = 0;
	ConsoleCursor.dwSize = 1;
	SetConsoleCursorInfo(consoleHandle, &ConsoleCursor);
}

// Ŀ�� ��ġ �̵� �Լ�
void ConsoleManager::GotoXY(const int& x, const int& y)
{
	HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);		// �ܼ� �ڵ� ��������
	COORD pos;
	pos.X = x;
	pos.Y = y;
	SetConsoleCursorPosition(consoleHandle, pos);
}

// ����ȭ�� �׸��� �Լ�
void ConsoleManager::DrawIntro()
{
	int x = 30, y = 26;		// �޴� ���� ǥ��(>) ��ġ ����

	system("cls");		// �ܼ� â �����
	GotoXY(0, 9);
	// �� �׸� ���
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
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0);		// �۾� ���� ����
				cout << "��";
			}
			else
			{
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 6);
				cout << "��";
			}
		}
		cout << endl;
	}
	// �����ϱ� ���
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
				cout << "��";
			}
			else
			{
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 4);
				cout << "��";
			}
		}
		cout << endl;
	}

	// ���� ���
	GotoXY(15, 23);
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 12);
	cout << "���� �������� ���ϳ�? �������� ������." << endl;

	// �޴� ���
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
	GotoXY(x-2, y);	// y = 26
	cout << "> ���� ����" << endl;
	GotoXY(x, y+2);	// y = 28
	cout << "   ����" << endl;
	GotoXY(x, y+4); // y = 30
	cout << "���� ���" << endl;
	GotoXY(x, y+6); // y = 32
	cout << "   ����" << endl;

	// Ű���� �Է� �޾Ƽ� �޴� ���� -> ��/�Ʒ� ����Ű�� �̵�, �����̽��ٷ� ����.
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
