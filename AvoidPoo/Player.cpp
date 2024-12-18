#include "Player.h"

// 플레이어 이동 함수
void Player::Move()
{
	// 우비 아이템 사용 중 이라면
	if (useItem)
	{
		// 플레이어 모양 변경
		console.DrawPlayer(x, y, State::RAINCOAT_IDEL);
	}
	else 
	{
		// 플레이어 기본 모양
		console.DrawPlayer(x, y, State::IDEL);
	}
	
	// 키보드 입력이 있으면
	if (_kbhit())
	{
		int key = InputKey::Input();
		switch (key)
		{
			// 플레이어 오른쪽으로 이동
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
			// 왼쪽으로 이동
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
			// 우비 아이템 사용
		case Key::R:
			UseItem(ItemType::COAT);
			break;
			// 물티슈 아이템 사용
		case Key::W:
			UseItem(ItemType::WIPES);
			break;
		}
	}
}

// 충돌 체크하는 함수
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

// 아이템 사용 함수
void Player::UseItem(const ItemType& type)
{
	// 인벤토리에 사용할 아이템 알려주고
	if (inven.UseItem(type))
	{
		// 아이템 종류에 따라 변동 적용
		switch (type)
		{
		case ItemType::COAT:
			// 우비는 똥 1번 막아줌
			useItem = true;
			break;
		case ItemType::WIPES:
			// 물티슈는 생명 +1
			if (health < 3)
			{
				health += 1;
				ShowHealth();
			}
			break;
		}
	}
	
}

// 코인 출력
void Player::ShowCoin() 
{
	console.DrawCoin(68, 0);
	console.GotoXY(77, 1);
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
	cout << coin << "코인";
}

// 플레이어 상태 출력 ( 사용 안 함 )
void Player::ShowStatus() const
{
	cout << "=====플레이어 상태=====" << endl;
	cout << "생명 : " << health << " 잔액 : " << coin << endl;
}

// 플레이어 생명 출력
void Player::ShowHealth()
{
	int hX = 67, hY = 5;
	console.GotoXY(hX, hY);
	for (int i = 0; i < health; i++)
	{
		// 꽉 찬 하트 출력
		console.DrawHealth(hX, hY);
		hX += 11;
	}

	for (int j = health; j < 3; j++)
	{
		// 빈 하트 출력
		console.DrawDeath(hX, hY);
		hX += 11;
	}
}
