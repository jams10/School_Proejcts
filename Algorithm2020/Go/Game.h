#pragma once

#include "Board.h"
#include "Player.h"
#include "Manager.h"

class Game
{
public:
	Game();
	// ���� ���� �Լ�
	void Go();
private:
	// �� ������ ���� ���� ���¸� �������ִ� �Լ�
	void Update();
	// �� ������ ���� ���� ȭ�� ������ִ� �Լ�
	void ComposeFrame();
public:
	Position ReplayPos;
private:
	// ���� ��ġ
	int TargetX = 0;
	int TargetY = 0;
	// ���� ����
	int GameRound = 0;
	// ���� �ܰ�( ���� - ���� - ���� ��)
	bool StartRound = true;
	bool EndRound = false;
	bool ReplayRound = false;
	/* ���� ��忡�� ��� */
	bool HasPass = false;
	Player CurPlayer;

	// �÷��̾� �迭
	Player Players[2];
	// �ٵ��� �ν��Ͻ�
	Board Board;
	// ���� �Ŵ��� �ν��Ͻ�
	Manager Man;
};