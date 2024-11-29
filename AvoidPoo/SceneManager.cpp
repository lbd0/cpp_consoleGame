#include "SceneManager.h"
using namespace std;
// 화면 변경하는 함수
void SceneManager::ChangeScene(int n)
{
	switch (n)
	{
	case Menu::GAME:
		system("cls");
		cout << "게임 화면";
		break;
	case Menu::SHOP:
		system("cls");
		cout << "상점 화면";
		break;
	case Menu::TUTORIAL:
		system("cls");
		cout << "게임방법 화면";
		break;
	case Menu::QUIT:
		// 게임 종료
		break;
	}
}
