#include "GameManager.h"

void GameManager::StartGame()
{
	console.Init();		// 콘솔 초기화
	console.DrawIntro();		// 시작화면 그리기
}
