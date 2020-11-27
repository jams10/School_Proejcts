#pragma once

#include <vector>
#include "Position.h"
#include "Icon.h"

#define OUT

class Board
{
public:
	Board();
	void SetBoardSize( const int& Size );
	// �Ű������� ���� ��ġ ���� 4���� �ٵϵ� üũ
	void CrossCheckStones( const int& TargetX, const int& TargetY,
		                   std::vector<std::string>& FourStones ) const;
	
	// ���� ������ ��� Ž���ϴ� �Լ�
	void FloodFill( const int& TargetX, const int& TargetY, const std::string& Target,
		            const std::string& Replace, bool& OUT HasExit, std::vector<Position>& Territory ) const;
	
	// Tromp - Taylor ���� �����ϴ� Reach Ž��. (���� ����� ���� ���� ���� ������ ���� ���)
	void SearchReach( const int& TargetX, const int& TargetY, 
		              std::vector<std::string>& Reached, std::vector<Position>& Territory ) const;
	// �ٵ��� �ʱ�ȭ
	void Reset();
public:
	// �ٵ��� ������ (BoardSize * BoardSize)
	int BoardSize = 8;
	// �ٵ��� ����
	std::vector<std::vector<Position>> M;
private:
};