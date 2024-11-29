#include "Player.h"

// 플레이어 이동 함수
void Player::Move(int& x, int& y)
{

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
