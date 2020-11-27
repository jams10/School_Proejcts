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
			std::cout << " " << std::setw( 3 ) << " < �� �� > ";
			break;
		case 2:
			if( GameRound % 2 == 0 )
			{
				std::cout << "    " << std::setw( 3 ) << " �� ";
			}
			else
			{
				std::cout << "    " << std::setw( 3 ) << " �� ";
			}
			break;
		case 4:
			std::cout << " " << std::setw( 3 ) << " < �� �� > ";
			break;
		case 6:
			std::cout << "  " << std::setw( 3 ) << "�� : " << Players[0].GetPassNumber() << " ȸ";
			std::cout << " / ���� �� : " << Players[0].GetStoneNumber() << " ��";
			break;
		case 7:
			std::cout << "  " << std::setw( 3 ) << "�� : " << Players[1].GetPassNumber() << " ȸ";
			std::cout << " / ���� �� : " << Players[1].GetStoneNumber() << " ��";
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
			std::cout << "�� : " << GameRound << " ��" << std::endl;
		}
		else
		{
			std::cout << "�� : " << GameRound << " ��" << std::endl;
		}
	}
	else
	{
		if( CurrentPlayer.GetPlayerColor() == BLACK )
		{
			std::cout << "�� : " << GameRound << " ��(�н�)" << std::endl;
		}
		else
		{
			std::cout << "�� : " << GameRound << " ��(�н�)" << std::endl;
		}
	}
}

bool Manager::PrintGameResult( const Player Players[], const Board& Board ) const
{
	int BlackScore = Players[0].GetScore();
	int WhiteScore = Players[1].GetScore();
	
	std::cout << std::endl;
	PrintOffSetX( WidthOffSet );
	std::cout << "�� : �� ���� ���� / �� : �� ���� ����" << std::endl << std::endl;
	PrintOffSetX( WidthOffSet );
	std::cout << "�� ���� : " << BlackScore << " / �� ���� : " << WhiteScore << std::endl;
	
	PrintOffSetX( WidthOffSet );
	if( BlackScore > WhiteScore )
	{
		std::cout << ">> �� �¸�!" << std::endl;
	}
	else if( BlackScore < WhiteScore )
	{
		std::cout << ">> �� �¸�!" << std::endl;
	}
	else
	{
		std::cout << ">> �����ϴ�!" << std::endl;
	}
	system( "pause" );

	char input = ' ';
	std::cout << std::endl;

	while( true )
	{
		system( "cls" );
		PrintOffSetY( HeightOffSet );
		PrintOffSetX( WidthOffSet );
		std::cout << "���� �Ͻðڽ��ϱ�? (Y/N) >> ";
		input = _getch();
		if( input == 'Y' || input == 'y' ) return true;
		else if( input == 'N' || input == 'n' ) return false;
		else
		{
			system( "cls" );
			PrintOffSetY( HeightOffSet );
			PrintOffSetX( WidthOffSet );
			std::cout << "�ùٸ� ���ڸ� �Է����ּ���" << std::endl;
			system( "pause" );
		}
	}
}

void Manager::StartScreen( Player Players[], Board& Board )
{
	PrintOffSetY( HeightOffSet );
	PrintOffSetX( WidthOffSet + 2 );
	std::cout << "< �� �� �� �� >" << std::endl << std::endl;
	PrintOffSetX( WidthOffSet - 1 );
	std::cout << "�ٵ��� ����� �Է����ּ���" << std::endl << std::endl;
	PrintOffSetX( WidthOffSet - 1 );
	std::cout << ">> ";
	
	int Size = 0;
	std::cin >> Size;
	
	// �ٵ��� ũ�� ����
	Board.SetBoardSize( Size );
	// �� �÷��̾� �ʱ� �ٵϵ� ���� ����
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
	// 1. ���� ó�� �浹�� �����ڸ����� �� �� ����.
	if( GameRound == 0 )
	{
		if( (TargetY > 0 && TargetY < Board.BoardSize - 1) &&
			(TargetX > 0 && TargetX < Board.BoardSize - 1) )
		{
			ERROR_MSG = "ó�� �浹�� �����ڸ����� ���� �� �ֽ��ϴ�.";
			ErrorHasOccured = true;
			return false;
		}
	}
	// 2. �̹� �ش� ������ �ٵϾ� ����
	else if( Board.M[TargetY][TargetX].Stone != EMPTY )
	{
		ERROR_MSG = "�̹� �ش� ������ �ٵϾ��� �����մϴ�.";
		ErrorHasOccured = true;
		return false;
	}
	// 2. �� ����
	else if( Board.M[TargetY][TargetX].Stone == KO )
	{
		ERROR_MSG = "���� ���ʿ� �ٵϾ��� �� �� �ֽ��ϴ�.";
		ErrorHasOccured = true;
		return false;
	}
	return true;
}

bool Manager::PutStone( const int& TargetX, const int& TargetY,
	                    const Player& Player, const int& GameRound, Board& Board )
{
	std::string Stone = Player.GetPlayerColor();

	// �ش� ������ �ٵϾ��� ���� �� �ִ��� üũ �� �ٵϾ� ����.
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

	// 1. �� ������ 4���� ������ ���ؼ� üũ
	Board.CrossCheckStones( X, Y, Stones );

	// 2. �ߺ� ��� ����	
	sort( Stones.begin(), Stones.end() );
	Stones.erase( unique( Stones.begin(), Stones.end() ), Stones.end() );

	// 3. �ߺ��� ��� ���� �Ͽ��� ��, ���Ұ� 1���� ������ 1���� ������ �ѷ� �ο� �ִٴ� ��.
	if( Stones.size() == 1 )
	{
		// �ش� ���� ����
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
	// �������� �ٵ��ǿ��� ������ �ٵϵ� ����
	std::string StoneMayBeCaptured = Player.GetPlayerColor();
	// �������� �ٵϵ���
	std::vector<Position> CapturePos;
	// Ko-Rule�� �ش��ϴ� �ٵϵ� ����
	std::string KoColor = EMPTY;

	for( int y = 0; y < Board.BoardSize; ++y )
	{
		for( int x = 0; x < Board.BoardSize; ++x )
		{
			bool HasExit = false;
			
			// 1. �� Ko ó��
			if( Board.M[y][x].Stone == EMPTY )
			{
				std::string Result = KoCheck( x, y, Board );
				if( Result != EMPTY )
				{
					KoColor = Result;
				}
			}

			// 2. �� ��ȹ ó��
			if( Board.M[y][x].Stone == StoneMayBeCaptured )
			{
				Board.FloodFill( x, y, StoneMayBeCaptured, EMPTY, HasExit, CapturePos );
				
				// Ż�ⱸ�� ���� ��� ���� �����Ǿ����Ƿ�, �ش� ���� �� ����
				if( !HasExit )
				{
					// �� ���� ó��
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
		ERROR_MSG = "O : ���� �� / �н��� ��� �ٵ��ǿ� ���ŵ��� �ʽ��ϴ�.";
	}
	else
	{
		ERROR_MSG = "WASD : �̵�, O : ����, P : �� �ѱ�";
	}
	ErrorHasOccured = true;
}

void Manager::CalcScore( Player Players[], Board& Board ) const
{
	for( int y = 0; y < Board.BoardSize; ++y )
	{
		for( int x = 0; x < Board.BoardSize; ++x )
		{
			// �� ������ ���� ����
			if( Board.M[y][x].Stone == EMPTY || Board.M[y][x].Stone == KO )
			{
				std::vector<std::string> Reached;
				std::vector<Position> Territory;
				
				Board.SearchReach( x, y, Reached, Territory );
				
				// �� ������ �� ���󿡸� Reach
				if( Reached.size() == 1 )
				{
					// �ش� ������ �� ������ ������.
					if( Players[0].GetPlayerColor() == Reached[0] )
					{
						for( const Position Pos : Territory )
						{
							Board.M[Pos.y][Pos.x].Stone = "��";
							Players[0].IncreaseScore();
						}
					}
					else
					{
						for( const Position Pos : Territory )
						{
							Board.M[Pos.y][Pos.x].Stone = "��";
							Players[1].IncreaseScore();
						}
					}
				}
			}
			// �� �÷��̾ ���� �� ����
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

