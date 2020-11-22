#include <iostream>
#include <iomanip>
#include "Board.h"

Board::Board()
{
    for( int i = 0; i < 8; ++i )
    {
        for( int j = 0; j < 8; ++j )
        {
            m[i][j] = "��";
        }
    }
}

void Board::Print( const Vec2& pos, const int& round ) const
{
    for( int i = 0; i < 8; ++i )
    {
        for( int j = 0; j < 8; ++j )
        {
            // ���� ��ġ vector ������ �޾� ���� ��ġ�� ǥ��
            if( pos.y == i && pos.x == j && m[i][j] == "��" )
            {
                if( round % 2 == 0 )
                {
                    // �浹 ������ ���� �鵹 ������ ��� ���� ��ġ ���� ǥ��
                    std::cout << std::setw( 3 ) << "��" << ' ';
                }
                else std::cout << std::setw( 3 ) << "��" << ' ';
                
            }
            else std::cout << std::setw( 3 ) << m[i][j] << ' ';
        }
        std::cout << std::endl;
    }
}

void Board::PutStone( const Vec2& pos, Player& player, OUT bool& valid )
{
    // ���� ���� ��ġ�� �� ������ �ƴϸ� ���� �� ����.
    if( m[pos.y][pos.x] != "��" )
    {
        valid = false;
        return;
    }
    std::string color = player.color;   // �ٵ� �� ����(���)

    player.PutStone( pos, color );      // ���� ���� ť�� �ٵϵ� ����

    m[pos.y][pos.x] = color;            // ���忡 �ݿ�
}

void Board::Skip( Player& player )
{
    player.PutStone( Vec2( 0, 0 ), "X" ); // ��ŵ �� ����� X�� �ϴ� �� �־���.
}

void Board::Update()
{

}
