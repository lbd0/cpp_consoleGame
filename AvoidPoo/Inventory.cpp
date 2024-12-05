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

// �κ��丮 map ��ȯ�ϴ� �Լ�
map<Item*, int> Inventory::GetItem()
{
	return invenItem;
}

// ����� �κ��丮 ���� ������ �� ����ϴ� �Լ�
void Inventory::SetCnt(Item* i, int n)
{
	auto it = invenItem.find(i);

	if (it != invenItem.end())
	{
		it->second = n;
	}

}

// �κ��丮�� ������ �߰� �Լ�
Item* Inventory::AddItem(int type)
{
	Item* item = new Item();
	// �Ű������� ���޹��� type�� ���� ������ �����Ͽ� invenItem�� ����.
	switch (type)
	{
	case 0:
		item = new RainCoat("���", 100, "���� 1�� ������.", ItemType::COAT);
		break;
	case 1:
		item = new WetWipes("��Ƽ��", 1000, "���� 1�� �۾���.", ItemType::WIPES);
		break;
	}
	pair<Item*, int> i (item, count);
	
	// �κ��丮�� ��� ������ �߰�.
	if (invenItem.empty())
	{
		i.second += 1;
		invenItem.insert(i);
	}
	else
	{
		for (auto& it : invenItem)
		{
			// �κ��丮�� ������ ���� ����.
			Item* item = it.first;
			if (item->GetType() == type)
			{
				it.second += 1;
				return item;
			}
		}
		// ������ �߰�.
		i.second += 1;
		invenItem.insert(i);
	}
	return item;
}

// ������ ��� �Լ�
bool Inventory::UseItem(const ItemType& type)
{
	for (auto& it : invenItem)
	{
		// �κ��丮���� ���� ���̰�
		Item* item = it.first;
		if (item->GetType() == type && it.second > 0)
		{
			it.second -= 1;
			// ������ ���
			//item->Skill();
			console.GotoXY(30, 5);
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
			cout << item->GetName() << " �������� ����մϴ�.";
			ShowCnt();
			Sleep(500);
			console.GotoXY(30, 5);
			cout << "                              ";
			return true;
		}
	}

	// �κ��丮�� �����۾����� ��� �Ұ�
	console.GotoXY(30, 5);
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
	cout << "�ش� �������� �����ϴ�." << endl;
	Sleep(500);
	console.GotoXY(30, 5);
	cout << "                              ";
	return false;
}

// ���� ȭ�鿡�� ������ ���� ���
void Inventory::ShowCnt()
{
	int x = 30, y = 2;
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
	for (const auto& pair : invenItem)
	{
		console.GotoXY(x, y);
		Item* it = pair.first;
		cout << it->GetName() << ": " << pair.second <<"��";
		x += 15;
 	}
}

// �κ��丮 ��� �Լ�
void Inventory::ShowInven() 
{
	console.GotoXY(0, 53);
	cout << "=====�κ��丮=====" << endl;
	for (const auto& pair : invenItem)
	{
		Item* it = pair.first;
		cout << it->GetName() << " : " << pair.second << endl;
	}
}
