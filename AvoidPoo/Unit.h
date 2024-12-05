#pragma once
#include <fstream>
#include <map>

// Ű����
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

// ���� �޴�
enum Menu
{
	GAME = 32,
	SHOP = 34,
	TUTORIAL = 36,
	QUIT = 38
};

// ������
enum ItemType
{
	COAT,
	WIPES,
	NONE
};

// �÷��̾� ����
enum State
{
	IDEL,
	MOVE,
	DIE,
	RAINCOAT_IDEL,
	RAINCOAT_MOVE
};

enum Drop
{
	POO,
	COIN
};
