#include "Inventory.h"

// �κ��丮�� ������ �߰� �Լ�
void Inventory::AddItem(Item* item)
{
	pair<Item*, int> i (item, count);
	
	// �κ��丮�� ��� ������ �߰�.
	if (invenItem.empty())
	{
		i.second += 1;
		invenItem.insert(i);
	}
	else
	{
		// �κ��丮�� ������ ���� ����
		auto it = invenItem.find(i.first);

		if (it != invenItem.end())
		{
			it->second += 1;
		}
	}
}

// ������ ��� �Լ�
void Inventory::UseItem(const ItemType& type)
{
	for (auto& it : invenItem)
	{
		// �κ��丮���� ���� ���̰�
		Item* item = it.first;
		if (item->GetType() == type)
		{
			it.second -= 1;
			// ������ ���
			item->Skill();
		}
		else
		{
			cout << "�ش� �������� �����ϴ�." << endl;
		}
	}
}

// �κ��丮 ��� �Լ�
void Inventory::ShowInven() const
{
	cout << "=====�κ��丮=====" << endl;
	for (const auto& pair : invenItem)
	{
		Item* it = pair.first;
		cout << it->GetName() << " : " << pair.second << endl;
	}
}
