#include "SceneManager.h"
using namespace std;
// ȭ�� �����ϴ� �Լ�
void SceneManager::ChangeScene(int n)
{
	switch (n)
	{
	case Menu::GAME:
		system("cls");
		cout << "���� ȭ��";
		break;
	case Menu::SHOP:
		system("cls");
		cout << "���� ȭ��";
		break;
	case Menu::TUTORIAL:
		system("cls");
		cout << "���ӹ�� ȭ��";
		break;
	case Menu::QUIT:
		// ���� ����
		break;
	}
}
