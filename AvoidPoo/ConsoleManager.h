#pragma once
#include "InputKey.h"
#include "SceneManager.h"
#include <windows.h>
#include <iostream>
#include <vector>
// �ܼ�â ���� �� �׸� �׸��� Ŭ����
class ConsoleManager
{
private:
	SceneManager sceneManager;
public:
	void Init();
	void GotoXY(const int& x, const int& y);
	void DrawIntro();
};

