#pragma once

#include <queue>
#include <string>
#include "Stone.h"

class Player
{
public:
	bool turn;                 // �÷��̾��� ���� ����
	int score;                 // �÷��̾��� ����(���� ũ�� = �ٵϾ� ����)
	int house;                 // �÷��̾��� �� ����
	int skip;                  // �÷��̾� ��ŵ Ƚ��
	std::string color;         // �÷��̾��� �ٵ� ��(���)
	std::queue<Stone*> qStone; // ���⸦ ���� �� �ٵ��� ť�� ����. (������ Ȯ��)
	std::queue<int> sss;
public:
	Player() = default;
	Player( int n );
	void PutStone( const Vec2& pos, const std::string& color );
};