#pragma once
// 키보드
enum Key
{
	UP = 72,
	DOWN = 80,
	LEFT = 75,
	RIGHT = 77,
	SPACE = 32,
	W = 119,
	R = 114
};

// 게임 메뉴
enum Menu
{
	GAME = 32,
	SHOP = 34,
	TUTORIAL = 36,
	QUIT = 38
};

// 아이템
enum class ItemType
{
	COAT,
	WIPES,
	NONE
};

enum State
{
	IDEL,
	MOVE,
	DIE
};