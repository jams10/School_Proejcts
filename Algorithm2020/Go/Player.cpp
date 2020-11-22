#include "Player.h"

Player::Player( int n )
	:
	turn( n ),
	score( 0 ),
	house( 0 ),
	skip( 0 )
{
	if( n == 0 ) color = "��";
	else color = "��";
}

/*
	Stone ���� �Ҵ� ���� �ʿ�

*/

void Player::PutStone( const Vec2& pos, const std::string& color )
{
	Stone* s = new Stone(pos, color);  // �Ű������� ������� �ٵϵ� ����
	qStone.push( s );                  // ť�� ����
}
