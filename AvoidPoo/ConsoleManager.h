#pragma once
#include "InputKey.h"
#include "SceneManager.h"
#include <windows.h>
#include <iostream>
#include <vector>
// 콘솔창 편집 및 그림 그리는 클래스
class ConsoleManager
{
private:
	SceneManager sceneManager;
public:
	void Init();
	void GotoXY(const int& x, const int& y);
	void DrawIntro();
};

