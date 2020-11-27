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
		// Replace = EMPTY 로 매개변수 줄 경우, 해당 위치가 이미 빈 공간이라는 의미.
		// 즉, 탈출구가 존재하므로 해당 영역에는 사로잡을 돌이 없음.
		HasExit = true;
		return;
	}
	// 반대되는 색의 돌인 경우
	if( M[TargetY][TargetX].Stone != Target ) return;
	
	// 이미 방문한 공간인 경우 패스
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
		// 빈 공간이 아닌 경우 해당 색깔의 돌을 벡터에 삽입. (KO 위치도 빈 공간 처리)
		// 추후 빈 공간이 한 색상에만 Reach(도달) 하는지 확인하기 위함.
		for( int i = 0; i < Reached.size(); ++i )
		{
			// 중복 방지
			if( Reached[i] == M[TargetY][TargetX].Stone ) return;
		}
		Reached.emplace_back( M[TargetY][TargetX].Stone );
		return;
	}

	// 이미 방문한 빈 공간인 경우 패스
	for( int i = 0; i < Territory.size(); ++i )
	{
		if( Territory[i].x == TargetX && Territory[i].y == TargetY ) return;
	}

	// 빈 공간은 점수 계산을 위한 영역 벡터에 삽입.
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
