#include "Inventory.h"

Inventory::Inventory() :count(0)
{
}

Inventory::~Inventory()
{
	invenItem.clear();
	map<Item*, int> temp(invenItem);
	temp.swap(invenItem);
}

// 인벤토리 map 반환하는 함수
map<Item*, int> Inventory::GetItem()
{
	return invenItem;
}

// 저장된 인벤토리 내용 적용할 때 사용하는 함수
void Inventory::SetCnt(Item* i, int n)
{
	auto it = invenItem.find(i);

	if (it != invenItem.end())
	{
		it->second = n;
	}

}

// 인벤토리에 아이템 추가 함수
Item* Inventory::AddItem(int type)
{
	Item* item = new Item();
	// 매개변수로 전달받은 type에 따라 아이템 생성하여 invenItem에 삽입.
	switch (type)
	{
	case 0:
		item = new RainCoat("우비", 100, "똥을 1번 막아줌.", ItemType::COAT);
		break;
	case 1:
		item = new WetWipes("물티슈", 1000, "똥을 1번 닦아줌.", ItemType::WIPES);
		break;
	}
	pair<Item*, int> i (item, count);
	
	// 인벤토리가 비어 있으면 추가.
	if (invenItem.empty())
	{
		i.second += 1;
		invenItem.insert(i);
	}
	else
	{
		for (auto& it : invenItem)
		{
			// 인벤토리에 있으면 개수 증가.
			Item* item = it.first;
			if (item->GetType() == type)
			{
				it.second += 1;
				return item;
			}
		}
		// 없으면 추가.
		i.second += 1;
		invenItem.insert(i);
	}
	return item;
}

// 아이템 사용 함수
bool Inventory::UseItem(const ItemType& type)
{
	for (auto& it : invenItem)
	{
		// 인벤토리에서 개수 줄이고
		Item* item = it.first;
		if (item->GetType() == type && it.second > 0)
		{
			it.second -= 1;
			// 아이템 사용
			//item->Skill();
			console.GotoXY(30, 5);
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
			cout << item->GetName() << " 아이템을 사용합니다.";
			ShowCnt();
			Sleep(500);
			console.GotoXY(30, 5);
			cout << "                              ";
			return true;
		}
	}

	// 인벤토리에 아이템없으면 사용 불가
	console.GotoXY(30, 5);
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
	cout << "해당 아이템이 없습니다." << endl;
	Sleep(500);
	console.GotoXY(30, 5);
	cout << "                              ";
	return false;
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
void Inventory::ShowInven() 
{
	console.GotoXY(0, 53);
	cout << "=====인벤토리=====" << endl;
	for (const auto& pair : invenItem)
	{
		Item* it = pair.first;
		cout << it->GetName() << " : " << pair.second << endl;
	}
}
