#pragma once

#include <queue>
#include <string>
#include "Stone.h"

class Player
{
public:
	bool turn;                 // 플레이어의 차례 여부
	int score;                 // 플레이어의 점수(집의 크기 = 바둑알 개수)
	int house;                 // 플레이어의 집 개수
	int skip;                  // 플레이어 스킵 횟수
	std::string color;         // 플레이어의 바둑 색(모양)
	std::queue<Stone*> qStone; // 복기를 위해 둔 바둑을 큐에 저장. (포인터 확인)
	std::queue<int> sss;
public:
	Player() = default;
	Player( int n );
	void PutStone( const Vec2& pos, const std::string& color );
};