#pragma once

#include <queue>
#include "Position.h"

class Player
{
public:
	Player() = default;
	
	// ���� �ٵϵ� ����
	void DeacreaseStoneNumber();
	// �н� Ƚ�� ����
	void IncreasePassNumber();
	// ���� ����
	void IncreaseScore();

	// �÷��̾� ���� ����
	void SetColor( const std::string& Color );
	// �÷��̾� �ִ� �ٵϵ� �� ����
	void SetMaxStone( const int& N );
	
	/* �÷��̾� ���� �޾ƿ��� �Լ��� */
	int GetScore() const;
	int GetStoneNumber() const;
	int GetPassNumber() const;
	std::string GetPlayerColor() const;
	
	// ���� ���� ���Ϳ� �÷��̾ �� �� ��ġ�� �����ϴ� �Լ�
	void PutStoneForReplay( const int& TargetX, const int& TargetY );
	Position PopStoneForReplay();

	// ť ������� ��ȸ
	bool QIsEmpty() const;
public:
private:
	// ����
	int Score = 0;
	// �ִ� �ٵϵ� ��(�ʱ� �־��� �ٵϵ�)
	int NStones = 0;
	// �н� Ƚ��
	int NPasses = 0;
	// �÷��̾� ����
	std::string Color = EMPTY;
	// ���⸦ ���� �� ����
	std::queue<Position> History;
};