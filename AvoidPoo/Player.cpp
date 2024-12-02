#include "Player.h"

// �÷��̾� �̵� �Լ�
void Player::Move(int& x, int& y)
{
	console.DrawPlayer(x, y, State::IDEL);
	if (_kbhit())
	{
		Key key = InputKey::Input();
		switch (key)
		{
		case Key::RIGHT:
			if (x < 66)
			{
				console.GotoXY(x, y);
				console.ErasePlayer(x, y);

				x += 1;
				console.GotoXY(x, y);
				console.DrawPlayer(x, y, State::MOVE);
				//Sleep(100);
			}
			break;
		case Key::LEFT:
			if (x > 0)
			{
				console.GotoXY(x, y);
				console.ErasePlayer(x, y);

				x -= 1;
				console.GotoXY(x, y);
				console.DrawPlayer(x, y, State::MOVE);
				//Sleep(100);
			}
			break;
		case Key::R:
			UseItem(ItemType::COAT);
			break;
		case Key::W:
			UseItem(ItemType::WIPES);
			break;
		}
	}
}

// ������ ��� �Լ�
void Player::UseItem(const ItemType& type)
{
	// �κ��丮�� ����� ������ �˷��ְ�
	inven.UseItem(type);
	// ������ ������ ���� ���� ����
	if (type == ItemType::WIPES)
	{
		// ��Ƽ���� ���� +1
		if(health < 3)
			health += 1;
	}
}

// ���� ���
void Player::ShowCoin() const
{
	cout << "====�ܾ�====" << endl;
	cout << coin << "����" << endl;
}

// �÷��̾� ���� ���
void Player::ShowStatus() const
{
	cout << "=====�÷��̾� ����=====" << endl;
	cout << "���� : " << health << " �ܾ� : " << coin << endl;
}

void Player::ShowHealth()
{
	int hX = 67, hY = 5;
	console.GotoXY(hX, hY);
	for (int i = 0; i < health; i++)
	{
		console.DrawHealth(hX, hY);
		hX += 11;
	}

	for (int j = health; j < 3; j++)
	{
		console.DrawDeath(hX, hY);
		hX += 11;
	}
}
