#include "Shop.h"

// �Ҹ���
Shop::~Shop()
{
	for (auto& it : items)
	{
		delete it;
		it = nullptr;
	}
}

// ������ ���� �Լ�
void Shop::BuyItem(const ItemType& type, int& coin, Inventory& inven )
{
	for (auto& it : items)
	{
		if (it->GetType() == type)
		{
			// �ܾ��� ����ϸ�
			if (it->GetPrice() <= coin)
			{
				// ������ ����
				coin -= it->GetPrice();
				inven.AddItem(it);
				cout << it->GetName() << "�� �����Ͽ����ϴ�. �ܾ� : " << coin << endl;
				inven.ShowInven();
			}
			else
			{
				cout << "������ �����մϴ�." << endl;
			}
		}
	}
}

// ������ ������ �߰� �Լ�
void Shop::AddItem(Item* item)
{
	if (find(items.begin(), items.end(), item) != items.end()) return;
	items.push_back(item);
}
