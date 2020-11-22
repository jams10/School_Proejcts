#include "Player.h"

Player::Player( int n )
	:
	turn( n ),
	score( 0 ),
	house( 0 ),
	skip( 0 )
{
	if( n == 0 ) color = "○";
	else color = "●";
}

/*
	Stone 동적 할당 해제 필요

*/

void Player::PutStone( const Vec2& pos, const std::string& color )
{
	Stone* s = new Stone(pos, color);  // 매개변수를 기반으로 바둑돌 생성
	qStone.push( s );                  // 큐에 삽입
}
