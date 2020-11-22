#include <iostream>
#include <iomanip>
#include "Board.h"

Board::Board()
{
    for( int i = 0; i < 8; ++i )
    {
        for( int j = 0; j < 8; ++j )
        {
            m[i][j] = "□";
        }
    }
}

void Board::Print( const Vec2& pos, const int& round ) const
{
    for( int i = 0; i < 8; ++i )
    {
        for( int j = 0; j < 8; ++j )
        {
            // 현재 위치 vector 정보를 받아 현재 위치를 표시
            if( pos.y == i && pos.x == j && m[i][j] == "□" )
            {
                if( round % 2 == 0 )
                {
                    // 흑돌 차례인 경우와 백돌 차례인 경우 현재 위치 따로 표시
                    std::cout << std::setw( 3 ) << "◆" << ' ';
                }
                else std::cout << std::setw( 3 ) << "◇" << ' ';
                
            }
            else std::cout << std::setw( 3 ) << m[i][j] << ' ';
        }
        std::cout << std::endl;
    }
}

void Board::PutStone( const Vec2& pos, Player& player, OUT bool& valid )
{
    // 돌을 놓을 위치가 빈 공간이 아니면 놓을 수 없음.
    if( m[pos.y][pos.x] != "□" )
    {
        valid = false;
        return;
    }
    std::string color = player.color;   // 바둑 돌 색깔(모양)

    player.PutStone( pos, color );      // 복기 위한 큐에 바둑돌 삽입

    m[pos.y][pos.x] = color;            // 보드에 반영
}

void Board::Skip( Player& player )
{
    player.PutStone( Vec2( 0, 0 ), "X" ); // 스킵 시 모양을 X로 하는 돌 넣어줌.
}

void Board::Update()
{

}
