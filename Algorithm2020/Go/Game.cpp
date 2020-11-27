#include <iostream>
#include <conio.h>
#include "Game.h"

Game::Game()
{
	Players[0].SetColor( BLACK );
	Players[1].SetColor( WHITE );
}

void Game::Go()
{
	ComposeFrame();
	while( !EndRound )
	{
		Update();
	}
	// 복기 까지 끝난 경우 바로 종료
	if( ReplayRound ) return;
	
	// 점수 계산
	Man.CalcScore( Players, Board );
	
	ComposeFrame();
	
	// 복기 선택 여부 확인
	if( Man.PrintGameResult( Players, Board ) )
	{
		ReplayRound = true;
		EndRound = false;
		// 바둑판 비우기
		Board.Reset();
		// 게임 라운드 초기화
		GameRound = 0;
		Players[0].SetMaxStone( 0 );
		Players[1].SetMaxStone( 0 );
		ComposeFrame();
		while( !EndRound )
		{
			Update();
		}
	}
	else return;
}

void Game::Update()
{
	char Input = ' ';
	Input = _getch();

	Player& CurrentPlayer = Players[GameRound % 2];
	Player& OtherPlayer = Players[(GameRound + 1) % 2];

	// 복기 모드
	if( ReplayRound )
	{
		CurPlayer = CurrentPlayer;
		if( CurrentPlayer.QIsEmpty() && OtherPlayer.QIsEmpty() )
		{
			EndRound = true;
		}

		if( Input == 'O' || Input == 'o' )
		{
			Position Pos;
			Pos = CurrentPlayer.PopStoneForReplay();
			ReplayPos = Pos;
			// 본인의 차례에 바둑 돌을 둔 경우
			if( Pos.x >=0 && Pos.y >= 0 )
			{
				Man.PutStone( Pos.x, Pos.y, CurrentPlayer, GameRound, Board );
				Man.UpdateBoard( OtherPlayer, GameRound, Board );
				HasPass = false;
			}
			// 본인의 차례에 패스한 경우
			if( Pos.x == -1 && Pos.y == -1 )
			{
				HasPass = true;
			}
			GameRound++;
			ComposeFrame();
			return;
		}
		else if(Input != ' ' )
		{
			Man.InputException( ReplayRound );
			ComposeFrame();
		}
		return;
	}

	// 두 플레이어 중 한 플레이어가 종료 조건 달성한 경우
	if( CurrentPlayer.GetPassNumber() >= 3 ||
		CurrentPlayer.GetStoneNumber() <= 0 )
	{
		Man.UpdateBoard( CurrentPlayer, GameRound, Board );
		Man.UpdateBoard( OtherPlayer, GameRound, Board );
		GameRound++;
		ComposeFrame();
		return;
	}

	// 플레이어 조작에 따른 Target 위치 변경
	if( Input == 'W' || Input == 'w' )
	{
		if( TargetY > 0 )
		{
			TargetY--;
		}
	}
	else if( Input == 'A' || Input == 'a' )
	{
		if( TargetX > 0 )
		{
			TargetX--;
		}
	}
	else if( Input == 'S' || Input == 's' )
	{
		if( TargetY + 1 < Board.BoardSize )
		{
			TargetY++;
		}
	}
	else if( Input == 'D' || Input == 'd' )
	{
		if( TargetX + 1 < Board.BoardSize )
		{
			TargetX++;
		}
	}
	// 패스 누른 경우
	else if( Input == 'P' || Input == 'p' )
	{
		CurrentPlayer.IncreasePassNumber();
		// 스킵한 경우 놓은 위치를 (-1,-1)로 주어 차후에 구분할 수 있도록 함.
		CurrentPlayer.PutStoneForReplay( -1, -1 );
		GameRound++;
	}
	// 바둑을 두기로 결정한 경우
	else if( Input == 'O' || Input == 'o' )
	{
		if( Man.PutStone( TargetX, TargetY, CurrentPlayer, GameRound, Board ) )
		{
			CurrentPlayer.DeacreaseStoneNumber();
			// 복기를 위한 벡터에 바둑돌 놓은 위치 삽입
			CurrentPlayer.PutStoneForReplay( TargetX, TargetY );
			Man.UpdateBoard( OtherPlayer, GameRound, Board );
			GameRound++;
		}
	}
	else
	{
		Man.InputException( ReplayRound );
	}

	// 게임 종료 조건 확인
	// 1. 두 플레이어가 모두 2번 이상 패스한 경우
	if( CurrentPlayer.GetPassNumber() >= 3 &&
		OtherPlayer.GetPassNumber() >= 3 )
	{
		EndRound = true;
	}
	// 2. 두 플레이어가 바둑돌을 모두 소진한 경우
	if( CurrentPlayer.GetStoneNumber() <= 0 &&
		OtherPlayer.GetStoneNumber() <= 0 )
	{
		EndRound = true;
	}

	// 게임 프레임 출력 호출
	if( Input != ' ' )
	{
		// 사용자로 부터 입력이 들어왔을 때만 프레임을 새로 그리도록 함.
		// 입력이 없을 때도 계속해서 그릴 경우, 화면 깜빡임이 더 자주 발생함.
		ComposeFrame();
	}
}

void Game::ComposeFrame()
{
	system( "cls" );
	if( StartRound )
	{
		/*
			< 게임 초기 시작 상황. 시작 화면 출력>
			StartScreen() 함수 호출해 시작화면 출력하고,
			Update() 함수에서 입력 체크 조건으로 인해 바둑판 화면으로 바로
			넘어가지 않기 때문에, 추가적으로 이 부분에만 화면 초기화 및
			바둑판 출력 함수를 삽입하였음.
		*/
		Man.StartScreen( Players, Board );
		system( "cls" );
		Man.PrintGameScreen( TargetX, TargetY, GameRound, Players, Board );
		StartRound = false;
	}
	else
	{
		Man.PrintGameScreen( TargetX, TargetY, GameRound, Players, Board );
	}
	Man.PrintError();
	if( ReplayRound )
	{
		Man.PrintReplayInfo( CurPlayer, GameRound, HasPass );
	}
}
