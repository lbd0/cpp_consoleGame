#include "Player.h"

// �÷��̾� �̵� �Լ�
void Player::Move()
{
	if (useItem)
	{
		console.DrawPlayer(x, y, State::RAINCOAT_IDEL);
	}
	else 
	{
		console.DrawPlayer(x, y, State::IDEL);
	}
	
	if (_kbhit())
	{
		int key = InputKey::Input();
		switch (key)
		{
		case Key::RIGHT:
			if (x < 66)
			{
				console.GotoXY(x, y);
				console.ErasePlayer(x, y);

				x += 2;
				console.GotoXY(x, y);
				if (useItem)
				{
					console.DrawPlayer(x, y, State::RAINCOAT_MOVE);
				}
				else
				{
					console.DrawPlayer(x, y, State::MOVE);
				}
			}
			break;
		case Key::LEFT:
			if (x > 0)
			{
				console.GotoXY(x, y);
				console.ErasePlayer(x, y);

				x -= 2;
				console.GotoXY(x, y);
				if (useItem)
				{
					console.DrawPlayer(x, y, State::RAINCOAT_MOVE);
				}
				else
				{
					console.DrawPlayer(x, y, State::MOVE);
				}
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

// �浹 üũ�ϴ� �Լ�
bool Player::IsCollision(int cx, int cy, Drop drop)
{
	if (cx >= x && cx < x + 42)
	{
		if (cy >= y && cy <= 58)
		{
			isColl = true;
			return isColl;
		}
	}
	isColl = false;
	return isColl;
}

// ������ ��� �Լ�
void Player::UseItem(const ItemType& type)
{
	// �κ��丮�� ����� ������ �˷��ְ�
	inven.UseItem(type);
	// ������ ������ ���� ���� ����
	switch (type)
	{
	case ItemType::COAT:
		// ���� �� 1�� ������
		useItem = true;
		break;
	case ItemType::WIPES:
		// ��Ƽ���� ���� +1
		if (health < 3)
		{
			health += 1;
			ShowHealth();
		}
		break;
	}
}

// ���� ���
void Player::ShowCoin() 
{
	console.DrawCoin(68, 0);
	console.GotoXY(77, 1);
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
	cout << coin << "����";
}

// �÷��̾� ���� ���
void Player::ShowStatus() const
{
	cout << "=====�÷��̾� ����=====" << endl;
	cout << "���� : " << health << " �ܾ� : " << coin << endl;
}

// �÷��̾� ���� ���
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
