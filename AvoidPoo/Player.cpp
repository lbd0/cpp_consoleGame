#include "Player.h"

// �÷��̾� �̵� �Լ�
void Player::Move(int& x, int& y)
{

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
