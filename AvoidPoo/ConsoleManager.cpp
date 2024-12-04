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

	GotoXY(10, 50);
	cout << "�̵� : ��/��, ���� : space";

	// Ű���� �Է� �޾Ƽ� �޴� ���� -> ��/�Ʒ� ����Ű�� �̵�, �����̽��ٷ� ����.
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

// ���� ȭ�� �׸��� �Լ�
void ConsoleManager::DrawGame(int best, int time)
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

// ��Ƽ�� ������ �׸��� �Լ�
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
void ConsoleManager::DrawShop(vector<Item*> items)
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


		int tx = 13, ty = 40;
		int index = 1;
		for (auto& item : items)
		{
			GotoXY(tx, ty);
			cout << index++ << ". " << item->GetName() << " (" << item->GetPrice() << "����)";
			GotoXY(tx, ty + 2);
			cout << "����: " << item->GetDesc();
			tx += 50;
		}
		int rainX = 7, rainY = 20;
		DrawPlayer(rainX, rainY, State::RAINCOAT_IDEL);

		int wipeX = 60, wipeY = 25;
		DrawWipe(wipeX, wipeY);

		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
		GotoXY(43, 48);
		cout << "0. ���ư���";
		GotoXY(35, 50);
		cout << "������ �������� �����ϼ���: ";

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

// ���ӹ�� Ÿ��Ʋ �׸��� �Լ�
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

// ���� ��� �׸��� �Լ�
void ConsoleManager::DrawTutorial()
{
	system("cls");
	DrawTutorialTitle(15, 3);
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
	GotoXY(15, 15);
	cout << "1. �÷��̾�� �¿� ����Ű�� �̿��Ͽ� �¿�� ������ �� �ֽ��ϴ�.";
	GotoXY(15, 17);
	cout << "2. ���� 3�� ������ GameOver!";
	GotoXY(15, 19);
	cout << "3. ������ ������ ������ ���� �� �ֽ��ϴ�. (�ݾ��� ����!)";
	GotoXY(15, 21);
	cout << "4. �ִ��� ���� �ð� ���� ���� ���ߺ�����.";
	GotoXY(15, 24);
	cout << "---------------------������---------------------";
	GotoXY(15, 26);
	cout << "1. ��� (100 ����) : ���� �� �� �� �����ݴϴ�.";
	GotoXY(15, 28);
	cout << "2. ��Ƽ�� (1000 ����) : ���� �� �� �۾��ݴϴ�. (���� +1)";
	GotoXY(15, 30);
	cout << "---------------------���۹�---------------------";
	GotoXY(15, 32);
	cout << "1. ���� ȭ��";
	GotoXY(15, 34);
	cout << "���� ����Ű�� �̿��Ͽ� �̵�, �����̽��ٸ� �̿��Ͽ� ������ �� �ֽ��ϴ�.";
	GotoXY(15, 36);
	cout << "2. ����";
	GotoXY(15, 38);
	cout << "�������� ��ȣ�� �Է��Ͽ� ������ ������ �� �ֽ��ϴ�. (1 : ���, 2 : ��Ƽ��)";
	GotoXY(15, 40);
	cout << "���� 1ȸ �̿� �� �ڵ����� ���� ȭ������ �̵��մϴ�.";
	GotoXY(15, 42);
	cout << "3. ����";
	GotoXY(15, 44);
	cout << "�¿� ����Ű�� �̿��Ͽ� �÷��̾ �����մϴ�.";
	GotoXY(15, 46);
	cout << "���� ���� �� �����̽��ٸ� �̿��Ͽ� ����ȭ������ �̵��� �� �ֽ��ϴ�.";

	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 6);
	GotoXY(40, 50);
	cout << "> ���ư��� (space)";

}

// ���� ���� �׸��� �Լ�
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
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0);		// �۾� ���� ����
				cout << "��";
			}
			else
			{
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 4);
				cout << "��";
			}
		}
	}

	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
	GotoXY(33, 30);
	cout << "��� : " << time << "��";
	GotoXY(55, 30);
	cout << "�ְ� ��� : " << best << "��";

	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
	GotoXY(43, 35);
	cout << "> ���ư��� (space)";

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

