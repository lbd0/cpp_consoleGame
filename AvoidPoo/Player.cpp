#include "Player.h"

// 플레이어 이동 함수
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

// 아이템 사용 함수
void Player::UseItem(const ItemType& type)
{
	// 인벤토리에 사용할 아이템 알려주고
	inven.UseItem(type);
	// 아이템 종류에 따라 변동 적용
	if (type == ItemType::WIPES)
	{
		// 물티슈는 생명 +1
		if(health < 3)
			health += 1;
	}
}

// 코인 출력
void Player::ShowCoin() const
{
	cout << "====잔액====" << endl;
	cout << coin << "코인" << endl;
}

// 플레이어 상태 출력
void Player::ShowStatus() const
{
	cout << "=====플레이어 상태=====" << endl;
	cout << "생명 : " << health << " 잔액 : " << coin << endl;
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
