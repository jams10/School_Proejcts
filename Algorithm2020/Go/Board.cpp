#include "Board.h"

Board::Board()
	:
	BoardSize( 8 )
{
	M.resize( 8 );
	for( int y = 0; y < 8; ++y )
	{
		for( int x = 0; x < 8; ++x )
		{
			M[y].emplace_back( Position( x, y ) );
		}
	}
}

void Board::SetBoardSize( const int& Size )
{
	if( Size == BoardSize ) return;

	BoardSize = Size;
	M.resize( Size );
	for( int y = 0; y < Size; ++y )
	{
		for( int x = 0; x < Size; ++x )
		{
			M[y].emplace_back( Position( x, y ) );
		}
	}
}


void Board::CrossCheckStones( const int& TargetX, const int& TargetY, 
	                          std::vector<std::string>& FourStones ) const
{
	if( TargetX > 0 && M[TargetY][TargetX - 1].Stone != EMPTY )
	{
		FourStones.emplace_back( M[TargetY][TargetX - 1].Stone );
	}
	if( TargetY > 0 && M[TargetY - 1][TargetX].Stone != EMPTY )
	{
		FourStones.emplace_back( M[TargetY - 1][TargetX].Stone );
	}
	if( TargetX < BoardSize - 1 && M[TargetY][TargetX + 1].Stone != EMPTY )
	{
		FourStones.emplace_back( M[TargetY][TargetX + 1].Stone );
	}
	if( TargetY < BoardSize - 1 && M[TargetY + 1][TargetX].Stone != EMPTY )
	{
		FourStones.emplace_back( M[TargetY + 1][TargetX].Stone );
	}
}


void Board::FloodFill( const int& TargetX, const int& TargetY, const std::string& Target,
	                   const std::string& Replace, bool& OUT HasExit, std::vector<Position>& Territory ) const
{
	if( TargetX < 0 || TargetX > BoardSize - 1 || TargetY < 0 || TargetY > BoardSize - 1 ) return;
	if( M[TargetY][TargetX].Stone == Replace || M[TargetY][TargetX].Stone == KO )
	{
		// Replace = EMPTY �� �Ű����� �� ���, �ش� ��ġ�� �̹� �� �����̶�� �ǹ�.
		// ��, Ż�ⱸ�� �����ϹǷ� �ش� �������� ������� ���� ����.
		HasExit = true;
		return;
	}
	// �ݴ�Ǵ� ���� ���� ���
	if( M[TargetY][TargetX].Stone != Target ) return;
	
	// �̹� �湮�� ������ ��� �н�
	for( int i = 0; i < Territory.size(); ++i )
	{
		if( Territory[i].x == TargetX && Territory[i].y == TargetY ) return;
	}

	Territory.emplace_back( M[TargetY][TargetX] );

	FloodFill( TargetX, TargetY - 1, Target, Replace, HasExit, Territory );
	FloodFill( TargetX, TargetY + 1, Target, Replace, HasExit, Territory );
	FloodFill( TargetX - 1, TargetY, Target, Replace, HasExit, Territory );
	FloodFill( TargetX + 1, TargetY, Target, Replace, HasExit, Territory );

	return;
}

void Board::SearchReach( const int& TargetX, const int& TargetY, 
	                     std::vector<std::string>& Reached, std::vector<Position>& Territory ) const
{
	if( TargetX < 0 || TargetX > BoardSize - 1 || TargetY < 0 || TargetY > BoardSize - 1 ) return;
	if( M[TargetY][TargetX].Stone != EMPTY && M[TargetY][TargetX].Stone != KO )
	{
		// �� ������ �ƴ� ��� �ش� ������ ���� ���Ϳ� ����. (KO ��ġ�� �� ���� ó��)
		// ���� �� ������ �� ���󿡸� Reach(����) �ϴ��� Ȯ���ϱ� ����.
		for( int i = 0; i < Reached.size(); ++i )
		{
			// �ߺ� ����
			if( Reached[i] == M[TargetY][TargetX].Stone ) return;
		}
		Reached.emplace_back( M[TargetY][TargetX].Stone );
		return;
	}

	// �̹� �湮�� �� ������ ��� �н�
	for( int i = 0; i < Territory.size(); ++i )
	{
		if( Territory[i].x == TargetX && Territory[i].y == TargetY ) return;
	}

	// �� ������ ���� ����� ���� ���� ���Ϳ� ����.
	Territory.emplace_back( Position( TargetX, TargetY ) );

	SearchReach( TargetX, TargetY - 1, Reached, Territory );
	SearchReach( TargetX, TargetY + 1, Reached, Territory );
	SearchReach( TargetX - 1, TargetY, Reached, Territory );
	SearchReach( TargetX + 1, TargetY, Reached, Territory );

	return;
}

void Board::Reset()
{
	for( int y = 0; y < BoardSize; ++y )
	{
		for( int x = 0; x < BoardSize; ++x )
		{
			M[y][x].Stone = EMPTY;
		}
	}
}
