# pragma once

#include <string>
#include "Vec2.h"
#include "Stone.h"
#include "Player.h"

#define OUT

class Board
{
	std::string m[8][8]; // �ٵ��� �迭
public:
	Board();
	// �ٵ��� ��� �Լ�
	void Print( const Vec2& pos, const int& round ) const;
	// �ٵϾ� ������ ���� ���� ó�� �Լ�
	void PutStone( const Vec2& pos, Player& player, OUT bool& valid );
	// �÷��̾� �� ��ŵ ó�� �Լ�
	void Skip( Player& player );
	// �ٵ��� ������Ʈ
	void Update();
};