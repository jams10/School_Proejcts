# pragma once

#include <string>
#include "Vec2.h"
#include "Stone.h"
#include "Player.h"

#define OUT

class Board
{
	std::string m[8][8]; // 바둑판 배열
public:
	Board();
	// 바둑판 출력 함수
	void Print( const Vec2& pos, const int& round ) const;
	// 바둑알 놓았을 때의 연산 처리 함수
	void PutStone( const Vec2& pos, Player& player, OUT bool& valid );
	// 플레이어 턴 스킵 처리 함수
	void Skip( Player& player );
	// 바둑판 업데이트
	void Update();
};