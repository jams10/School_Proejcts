#pragma once

#include <queue>
#include "Position.h"

class Player
{
public:
	Player() = default;
	
	// 소지 바둑돌 감소
	void DeacreaseStoneNumber();
	// 패스 횟수 증가
	void IncreasePassNumber();
	// 점수 증가
	void IncreaseScore();

	// 플레이어 색상 설정
	void SetColor( const std::string& Color );
	// 플레이어 최대 바둑돌 수 설정
	void SetMaxStone( const int& N );
	
	/* 플레이어 정보 받아오는 함수들 */
	int GetScore() const;
	int GetStoneNumber() const;
	int GetPassNumber() const;
	std::string GetPlayerColor() const;
	
	// 복기 위한 벡터에 플레이어가 둔 수 위치를 저장하는 함수
	void PutStoneForReplay( const int& TargetX, const int& TargetY );
	Position PopStoneForReplay();

	// 큐 비었는지 조회
	bool QIsEmpty() const;
public:
private:
	// 점수
	int Score = 0;
	// 최대 바둑돌 수(초기 주어진 바둑돌)
	int NStones = 0;
	// 패스 횟수
	int NPasses = 0;
	// 플레이어 색상
	std::string Color = EMPTY;
	// 복기를 위한 수 저장
	std::queue<Position> History;
};