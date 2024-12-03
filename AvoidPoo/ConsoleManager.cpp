#include "ConsoleManager.h"
using namespace std;
// �ܼ�â �ʱ�ȭ �� Ŀ�� ����� �Լ�
void ConsoleManager::Init()
{
	// �ܼ� â ũ�� �� �̸� ����
	system("mode con:cols=100 lines=63 | title AvoidPoo");

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
Menu ConsoleManager::DrawIntro()
{
	int x = 46, y = 32;		// �޴� ���� ǥ��(>) ��ġ ����

	system("cls");		// �ܼ� â �����
	int tX = 15, tY = 15;
	
	// �� �׸� ���
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
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0);		// �۾� ���� ����
				cout << "��";
			}
			else
			{
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 6);
				cout << "��";
			}
		}
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
		GotoXY(tX, tY++);
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
	}

	// ���� ���
	GotoXY(33, 29);
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 12);
	cout << "���� �������� ���ϳ�? �������� ������." << endl;

	// �޴� ���
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
	GotoXY(x-2, y);	// y = 32
	cout << "> ���� ����" << endl;
	GotoXY(x, y+2);	// y = 34
	cout << "   ����" << endl;
	GotoXY(x, y+4); // y = 36
	cout << "���� ���" << endl;
	GotoXY(x, y+6); // y = 38
	cout << "   ����" << endl;

	// Ű���� �Է� �޾Ƽ� �޴� ���� -> ��/�Ʒ� ����Ű�� �̵�, �����̽��ٷ� ����.
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

// ���� ȭ�� �׸��� �Լ�
void ConsoleManager::DrawGame(int best, double time)
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
	// �ð� �� ���
	GotoXY(2, 2);
	cout << "�ְ� ��� : " << best << "��";

	GotoXY(2, 6);
	cout << time << "��";

}

// �� �׸��� �Լ�
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
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0);		// �۾� ���� ����
				cout << "��";
			}
			else
			{
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 6);
				cout << "��";
			}
		}
	}
}

// �� ����� �Լ�
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

// ���� (��Ʈ) �׸��� �Լ�
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
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0);		// �۾� ���� ����
				cout << "��";
			}
			else
			{
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 12);
				cout << "��";
			}
		}
	}
}

// ����Ʈ �׸��� �Լ�
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
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0);		// �۾� ���� ����
				cout << "��";
			}
			else
			{
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 12);
				cout << "��";
			}
		}
	}
}

// �÷��̾� �׸��� �Լ�
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
					SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0);		// �۾� ���� ����
					cout << "��";
					break;
				case 1:
					SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
					cout << "��";
					break;
				case 3:
					SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
					cout << "��";
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
					SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0);		// �۾� ���� ����
					cout << "��";
					break;
				case 1:
					SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
					cout << "��";
					break;
				case 3: 
					SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
					cout << "��";
					break;
				case 2:
					SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 14);
					cout << "��";
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
					SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0);		// �۾� ���� ����
					cout << "��";
				}
				else if(p ==1)
				{
					SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),15);
					cout << "��";
				}
				else
				{
					SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 4);
					cout << "��";
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
					SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0);		// �۾� ���� ����
					cout << "��";
					break;
				case 1 :
					SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
					cout << "��";
					break;
				case 3:
					SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 9);
					cout << "��";
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
					SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0);		// �۾� ���� ����
					cout << "��";
					break;
				case 1:
					SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
					cout << "��";
					break;
				case 2:
					SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 14);
					cout << "��";
					break;
				case 3:
					SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 9);
					cout << "��";
					break;
				}
			}
		}
		break;
	}
}

// �÷��̾� ����� �Լ�
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

// ���� �׸��� �Լ�
int ConsoleManager::DrawShop(vector<Item*> items)
{
		
		GotoXY(35, 5);
		cout << "  ��    ��    ����  ��";
		GotoXY(35, 6);
		cout << "��  ��  ���    ��  ���";
		GotoXY(35, 7);
		cout << "        ��    ��  ��  ��";
		GotoXY(35, 8);
		cout << "      ��          ����";
		GotoXY(35, 9);
		cout << "    ��  ��        ��  ��";
		GotoXY(35, 10);
		cout << "      ��          ����";

		int x = 10, y = 40;
		int index = 1;
		for (auto& item : items)
		{
			GotoXY(x, y);
			cout << index++ << ". " << item->GetName() << " ���� : " << item->GetPrice() << "����";
			GotoXY(x, y + 1);
			cout << "����: " << item->GetDesc();
			x += 53;
		}

		GotoXY(35, 50);
		cout << "������ �������� �����ϼ���: ";
		int num;
		cin >> num;

		return num;
}

// ���� �׸��� �Լ�
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
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0);		// �۾� ���� ����
				cout << "��";
			}
			else
			{
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 14);
				cout << "��";
			}
		}
	}
}

// ���� ����� �Լ�
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

// ȭ�� �����ϴ� �Լ�
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

