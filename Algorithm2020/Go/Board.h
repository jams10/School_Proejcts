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
	// 매개변수로 들어온 위치 기준 4방향 바둑돌 체크
	void CrossCheckStones( const int& TargetX, const int& TargetY,
		                   std::vector<std::string>& FourStones ) const;
	
	// 포위 공간을 재귀 탐색하는 함수
	void FloodFill( const int& TargetX, const int& TargetY, const std::string& Target,
		            const std::string& Replace, bool& OUT HasExit, std::vector<Position>& Territory ) const;
	
	// Tromp - Taylor 에서 제시하는 Reach 탐색. (점수 계산을 위한 영역 주인 결정을 위해 사용)
	void SearchReach( const int& TargetX, const int& TargetY, 
		              std::vector<std::string>& Reached, std::vector<Position>& Territory ) const;
	// 바둑판 초기화
	void Reset();
public:
	// 바둑판 사이즈 (BoardSize * BoardSize)
	int BoardSize = 8;
	// 바둑판 벡터
	std::vector<std::vector<Position>> M;
private:
};