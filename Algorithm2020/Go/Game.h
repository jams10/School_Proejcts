#pragma once

#include "Board.h"
#include "Stone.h"
#include "Player.h"
#include "Vec2.h"

enum Condition
{
	NOTHING,
	OVER_SKIP_COUNTS,   // ��ŵ Ƚ�� �ʰ�
	INPUT_EXCEPTION,    // �Է� ����
	BLACK_PUT_STONE,    // ó�� �浹 �����ڸ� ����
	PUT_ERROR,          // �ٵϵ� �� �� ����
	ETC
};

class Game
{
	Board board;       // �ٵ��� �ν��Ͻ�
	bool gameStart;    // ���� ���� ����
	bool gameEnd;      // ���� ���� ����
	int round;         // ���� ����
	int cond;          // ��Ÿ ���� ����
	Vec2 currentPos;   // ���� ��ġ
	Player players[2]; // �÷��̾� �ν��Ͻ�
public:
	Game();
	void Go();           // ���� ����
	void Update();       // ���� ������Ʈ
	void Compose();      // ���� ȭ�� ���
	void PrintState();   // ���� �� ���� �� ���
	void Notification(); // ��Ÿ ���� �˸� ��� �Լ�
};