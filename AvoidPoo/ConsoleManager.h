#pragma once
#include "InputKey.h"
#include "Item.h"
#include <windows.h>
#include <iostream>
#include <vector>
// �ܼ�â ���� �� �׸� �׸��� Ŭ����
class ConsoleManager
{
private:
public:
	void Init();
	void GotoXY(const int& x, const int& y);
	Menu ChangeScene(int n);
	Menu DrawIntro();
	void DrawGame(int best, int time);
	void DrawPoo(int x, int y);
	void ErasePoo(int x, int y);
	void DrawHealth(int x, int y);
	void DrawDeath(int x, int y);
	void DrawPlayer(int x, int y, State state);
	void ErasePlayer(int x, int y);
	int DrawShop(vector<Item*> items);
	void DrawCoin(int x, int y);
	void EraseCoin(int x, int y);
};

