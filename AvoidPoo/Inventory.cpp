#include "Inventory.h"

// 인벤토리에 아이템 추가 함수
void Inventory::AddItem(Item* item)
{
	pair<Item*, int> i (item, count);
	
	// 인벤토리가 비어 있으면 추가.
	if (invenItem.empty())
	{
		i.second += 1;
		invenItem.insert(i);
	}
	else
	{
		// 인벤토리에 있으면 개수 증가
		auto it = invenItem.find(i.first);

		if (it != invenItem.end())
		{
			it->second += 1;
		}
	}
}

// 아이템 사용 함수
void Inventory::UseItem(const ItemType& type)
{
	for (auto& it : invenItem)
	{
		// 인벤토리에서 개수 줄이고
		Item* item = it.first;
		if (item->GetType() == type)
		{
			it.second -= 1;
			// 아이템 사용
			item->Skill();
		}
		else
		{
			cout << "해당 아이템이 없습니다." << endl;
		}
	}
}

// 인벤토리 출력 함수
void Inventory::ShowInven() const
{
	cout << "=====인벤토리=====" << endl;
	for (const auto& pair : invenItem)
	{
		Item* it = pair.first;
		cout << it->GetName() << " : " << pair.second << endl;
	}
}
