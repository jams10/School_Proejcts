#include "Player.h"

void Player::DeacreaseStoneNumber()
{
	NStones--;
}

void Player::IncreasePassNumber()
{
	NPasses++;
}

void Player::IncreaseScore()
{
	Score++;
}

void Player::SetColor( const std::string& Color )
{
	this->Color = Color;
}

void Player::SetMaxStone( const int& N )
{
	NStones = N;
}

int Player::GetScore() const
{
	return Score;
}

int Player::GetStoneNumber() const
{
	return NStones;
}

int Player::GetPassNumber() const
{
	return NPasses;
}

std::string Player::GetPlayerColor() const
{
	return Color;
}

void Player::PutStoneForReplay( const int& TargetX, const int& TargetY )
{
	History.push( Position( TargetX, TargetY ) );
}

Position Player::PopStoneForReplay()
{
	if( !History.empty() )
	{
		Position Pos = History.front();
		History.pop();
		return Pos;
	}
	else
	{
		return Position( -2, -2 );
	}
}

bool Player::QIsEmpty() const
{
	return History.empty();
}
