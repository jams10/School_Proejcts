#include <iostream>
#include <iomanip>
#include <algorithm>
#include <conio.h>
#include "Manager.h"

Manager::Manager()
{
}

void Manager::PrintOffSetY( const int& OffSet ) const
{
	for( int y = 0; y < OffSet; ++y )
	{
		std::cout << std::endl;
	}
}

void Manager::PrintOffSetX( const int& OffSet ) const
{
	for( int x = 0; x < OffSet; ++x )
	{
		std::cout << "  ";
	}
}

void Manager::PrintGameScreen( const int& TargetX, const int& TatgetY, 
	                           const int& GameRound, const Player Players[], const Board& Board ) const
{
	PrintOffSetY( HeightOffSet );
	for( int y = 0; y < Board.BoardSize; ++y )
	{
		PrintOffSetX( WidthOffSet );
		for( int x = 0; x < Board.BoardSize; ++x )
		{
			if( y == TatgetY && x == TargetX )
			{
				std::cout << std::setw( 2 ) << TARGET;
			}
			/*
			else if( M[y][x] == KO )
			{
				std::cout << std::setw( 2 ) << EMPTY;
			}
			*/
			else
			{
				std::cout << std::setw( 2 ) << Board.M[y][x].Stone;
			}
		}
		switch( y )
		{
		case 0:
			std::cout << " " << std::setw( 3 ) << " < 차 례 > ";
			break;
		case 2:
			if( GameRound % 2 == 0 )
			{
				std::cout << "    " << std::setw( 3 ) << " 흑 ";
			}
			else
			{
				std::cout << "    " << std::setw( 3 ) << " 백 ";
			}
			break;
		case 4:
			std::cout << " " << std::setw( 3 ) << " < 정 보 > ";
			break;
		case 6:
			std::cout << "  " << std::setw( 3 ) << "흑 : " << Players[0].GetPassNumber() << " 회";
			std::cout << " / 남은 돌 : " << Players[0].GetStoneNumber() << " 개";
			break;
		case 7:
			std::cout << "  " << std::setw( 3 ) << "백 : " << Players[1].GetPassNumber() << " 회";
			std::cout << " / 남은 돌 : " << Players[1].GetStoneNumber() << " 개";
			break;
		default:
			break;
		}
		std::cout << std::endl;
	}
}

void Manager::PrintError()
{
	std::cout << std::endl;
	PrintOffSetX( WidthOffSet );
	if( ErrorHasOccured )
	{
		std::cout << ERROR_MSG << std::endl;
		ErrorHasOccured = false;
	}
}

void Manager::PrintReplayInfo( const Player& CurrentPlayer, const int& GameRound, const bool& HasPass ) const
{
	if( !HasPass )
	{
		if( CurrentPlayer.GetPlayerColor() == BLACK )
		{
			std::cout << "흑 : " << GameRound << " 수" << std::endl;
		}
		else
		{
			std::cout << "백 : " << GameRound << " 수" << std::endl;
		}
	}
	else
	{
		if( CurrentPlayer.GetPlayerColor() == BLACK )
		{
			std::cout << "흑 : " << GameRound << " 수(패스)" << std::endl;
		}
		else
		{
			std::cout << "백 : " << GameRound << " 수(패스)" << std::endl;
		}
	}
}

bool Manager::PrintGameResult( const Player Players[], const Board& Board ) const
{
	int BlackScore = Players[0].GetScore();
	int WhiteScore = Players[1].GetScore();
	
	std::cout << std::endl;
	PrintOffSetX( WidthOffSet );
	std::cout << "♡ : 흑 점유 영역 / ♥ : 백 점유 영역" << std::endl << std::endl;
	PrintOffSetX( WidthOffSet );
	std::cout << "흑 점수 : " << BlackScore << " / 백 점수 : " << WhiteScore << std::endl;
	
	PrintOffSetX( WidthOffSet );
	if( BlackScore > WhiteScore )
	{
		std::cout << ">> 흑 승리!" << std::endl;
	}
	else if( BlackScore < WhiteScore )
	{
		std::cout << ">> 백 승리!" << std::endl;
	}
	else
	{
		std::cout << ">> 비겼습니다!" << std::endl;
	}
	system( "pause" );

	char input = ' ';
	std::cout << std::endl;

	while( true )
	{
		system( "cls" );
		PrintOffSetY( HeightOffSet );
		PrintOffSetX( WidthOffSet );
		std::cout << "복기 하시겠습니까? (Y/N) >> ";
		input = _getch();
		if( input == 'Y' || input == 'y' ) return true;
		else if( input == 'N' || input == 'n' ) return false;
		else
		{
			system( "cls" );
			PrintOffSetY( HeightOffSet );
			PrintOffSetX( WidthOffSet );
			std::cout << "올바른 문자를 입력해주세요" << std::endl;
			system( "pause" );
		}
	}
}

void Manager::StartScreen( Player Players[], Board& Board )
{
	PrintOffSetY( HeightOffSet );
	PrintOffSetX( WidthOffSet + 2 );
	std::cout << "< 바 둑 게 임 >" << std::endl << std::endl;
	PrintOffSetX( WidthOffSet - 1 );
	std::cout << "바둑판 사이즈를 입력해주세요" << std::endl << std::endl;
	PrintOffSetX( WidthOffSet - 1 );
	std::cout << ">> ";
	
	int Size = 0;
	std::cin >> Size;
	
	// 바둑판 크기 설정
	Board.SetBoardSize( Size );
	// 각 플레이어 초기 바둑돌 개수 설정
	if( Size % 2 == 0 )
	{
		Players[0].SetMaxStone( Size * Size / 2 );
		Players[1].SetMaxStone( Size * Size / 2 - 1 );
	}
	else
	{
		Players[0].SetMaxStone( Size * Size / 2 + 1 );
		Players[1].SetMaxStone( Size * Size / 2 );
	}
}

bool Manager::IsValidSpace( const int& TargetX, const int& TargetY, 
	                        const int& GameRound, Board& Board )
{
	// 1. 제일 처음 흑돌은 가장자리에만 둘 수 있음.
	if( GameRound == 0 )
	{
		if( (TargetY > 0 && TargetY < Board.BoardSize - 1) &&
			(TargetX > 0 && TargetX < Board.BoardSize - 1) )
		{
			ERROR_MSG = "처음 흑돌은 가장자리에만 놓을 수 있습니다.";
			ErrorHasOccured = true;
			return false;
		}
	}
	// 2. 이미 해당 공간에 바둑알 존재
	else if( Board.M[TargetY][TargetX].Stone != EMPTY )
	{
		ERROR_MSG = "이미 해당 공간에 바둑알이 존재합니다.";
		ErrorHasOccured = true;
		return false;
	}
	// 2. 패 공간
	else if( Board.M[TargetY][TargetX].Stone == KO )
	{
		ERROR_MSG = "다음 차례에 바둑알을 둘 수 있습니다.";
		ErrorHasOccured = true;
		return false;
	}
	return true;
}

bool Manager::PutStone( const int& TargetX, const int& TargetY,
	                    const Player& Player, const int& GameRound, Board& Board )
{
	std::string Stone = Player.GetPlayerColor();

	// 해당 공간에 바둑알을 놓을 수 있는지 체크 후 바둑알 놓기.
	if( IsValidSpace( TargetX, TargetY, GameRound, Board ) )
	{
		Board.M[TargetY][TargetX].Stone = Stone;
		return true;
	}
	else return false;
}

std::string Manager::KoCheck( const int& X, const int& Y, const Board& Board )
{
	std::vector<std::string> Stones;

	// 1. 빈 공간의 4방향 공간에 대해서 체크
	Board.CrossCheckStones( X, Y, Stones );

	// 2. 중복 요소 삭제	
	sort( Stones.begin(), Stones.end() );
	Stones.erase( unique( Stones.begin(), Stones.end() ), Stones.end() );

	// 3. 중복을 모두 제거 하였을 때, 원소가 1개가 남으면 1가지 색으로 둘러 싸여 있다는 뜻.
	if( Stones.size() == 1 )
	{
		// 해당 돌을 리턴
		return Stones[0];
	}
	else
	{
		return EMPTY;
	}
}

void Manager::UpdateBoard( const Player& Player, const int& GameRound, Board& Board )
{
	ResetKo( Board );
	// 포위당해 바둑판에서 삭제할 바둑돌 색상
	std::string StoneMayBeCaptured = Player.GetPlayerColor();
	// 포위당한 바둑돌들
	std::vector<Position> CapturePos;
	// Ko-Rule에 해당하는 바둑돌 색상
	std::string KoColor = EMPTY;

	for( int y = 0; y < Board.BoardSize; ++y )
	{
		for( int x = 0; x < Board.BoardSize; ++x )
		{
			bool HasExit = false;
			
			// 1. 돌 Ko 처리
			if( Board.M[y][x].Stone == EMPTY )
			{
				std::string Result = KoCheck( x, y, Board );
				if( Result != EMPTY )
				{
					KoColor = Result;
				}
			}

			// 2. 돌 포획 처리
			if( Board.M[y][x].Stone == StoneMayBeCaptured )
			{
				Board.FloodFill( x, y, StoneMayBeCaptured, EMPTY, HasExit, CapturePos );
				
				// 탈출구가 없을 경우 완전 포위되었으므로, 해당 영역 돌 삭제
				if( !HasExit )
				{
					// 패 영역 처리
					if( KoColor != EMPTY && CapturePos.size() == 1 &&
						CapturePos[0].Stone == KoColor )
					{
						Board.M[CapturePos[0].y][CapturePos[0].x].IsKo = true;
						Board.M[CapturePos[0].y][CapturePos[0].x].Stone = KO;
						Kos.emplace_back( CapturePos[0] );
					}
					else
					{
						for( Position Pos : CapturePos )
						{
							Board.M[Pos.y][Pos.x].Stone = EMPTY;
						}
					}
				}
				while( !CapturePos.empty() )
				{
					CapturePos.pop_back();
				}
			}
		}
	}
}

void Manager::ResetKo( Board& Board )
{
	for( int i = 0; i < Kos.size(); ++i )
	{
		Board.M[Kos[i].y][Kos[i].x].IsKo = false;
		Board.M[Kos[i].y][Kos[i].x].Stone = EMPTY;
	}
	while( !Kos.empty() )
	{
		Kos.pop_back();
	}
}

void Manager::InputException( const bool& ReplayRound )
{
	if( ReplayRound )
	{
		ERROR_MSG = "O : 다음 수 / 패스한 경우 바둑판에 갱신되지 않습니다.";
	}
	else
	{
		ERROR_MSG = "WASD : 이동, O : 착수, P : 턴 넘김";
	}
	ErrorHasOccured = true;
}

void Manager::CalcScore( Player Players[], Board& Board ) const
{
	for( int y = 0; y < Board.BoardSize; ++y )
	{
		for( int x = 0; x < Board.BoardSize; ++x )
		{
			// 빈 영역에 대한 점수
			if( Board.M[y][x].Stone == EMPTY || Board.M[y][x].Stone == KO )
			{
				std::vector<std::string> Reached;
				std::vector<Position> Territory;
				
				Board.SearchReach( x, y, Reached, Territory );
				
				// 빈 영역이 한 색상에만 Reach
				if( Reached.size() == 1 )
				{
					// 해당 영역은 그 색상이 점유함.
					if( Players[0].GetPlayerColor() == Reached[0] )
					{
						for( const Position Pos : Territory )
						{
							Board.M[Pos.y][Pos.x].Stone = "♡";
							Players[0].IncreaseScore();
						}
					}
					else
					{
						for( const Position Pos : Territory )
						{
							Board.M[Pos.y][Pos.x].Stone = "♥";
							Players[1].IncreaseScore();
						}
					}
				}
			}
			// 각 플레이어가 놓은 돌 점수
			else if( Board.M[y][x].Stone == BLACK )
			{
				Players[0].IncreaseScore();
			}
			else if( Board.M[y][x].Stone == WHITE )
			{
				Players[1].IncreaseScore();
			}
		}
	}
}

