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
		else
		{
			i.second += 1;
			invenItem.insert(i);
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
		if (item->GetType() == type && it.second > 0)
		{
			it.second -= 1;
			// 아이템 사용
			item->Skill();
			console.GotoXY(30, 5);
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
			cout << item->GetName() << " 아이템을 사용합니다.";
			ShowCnt();
			Sleep(500);
			console.GotoXY(30, 5);
			cout << "                              ";
		}
		else
		{
			console.GotoXY(30, 5);
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
			cout << "해당 아이템이 없습니다." << endl;
			Sleep(500);
			console.GotoXY(30, 5);
			cout << "                              ";
		}
	}
}

// 게임 화면에서 아이템 개수 출력
void Inventory::ShowCnt()
{
	int x = 30, y = 2;
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
	for (const auto& pair : invenItem)
	{
		console.GotoXY(x, y);
		Item* it = pair.first;
		cout << it->GetName() << ": " << pair.second <<"개";
		x += 15;
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
