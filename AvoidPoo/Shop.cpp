#include "Shop.h"

// 소멸자
Shop::~Shop()
{
	for (auto& it : items)
	{
		delete it;
		it = nullptr;
	}
}

// 아이템 구매 함수
void Shop::BuyItem(const ItemType& type, int& coin, Inventory& inven )
{
	for (auto& it : items)
	{
		if (it->GetType() == type)
		{
			// 잔액이 충분하면
			if (it->GetPrice() <= coin)
			{
				// 아이템 구매
				coin -= it->GetPrice();
				inven.AddItem(it);
				cout << it->GetName() << "을 구매하였습니다. 잔액 : " << coin << endl;
				inven.ShowInven();
			}
			else
			{
				cout << "코인이 부족합니다." << endl;
			}
		}
	}
}

// 상점에 아이템 추가 함수
void Shop::AddItem(Item* item)
{
	if (find(items.begin(), items.end(), item) != items.end()) return;
	items.push_back(item);
}
