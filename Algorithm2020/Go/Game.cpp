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
	// ���� ���� ���� ��� �ٷ� ����
	if( ReplayRound ) return;
	
	// ���� ���
	Man.CalcScore( Players, Board );
	
	ComposeFrame();
	
	// ���� ���� ���� Ȯ��
	if( Man.PrintGameResult( Players, Board ) )
	{
		ReplayRound = true;
		EndRound = false;
		// �ٵ��� ����
		Board.Reset();
		// ���� ���� �ʱ�ȭ
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

	// ���� ���
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
			// ������ ���ʿ� �ٵ� ���� �� ���
			if( Pos.x >=0 && Pos.y >= 0 )
			{
				Man.PutStone( Pos.x, Pos.y, CurrentPlayer, GameRound, Board );
				Man.UpdateBoard( OtherPlayer, GameRound, Board );
				HasPass = false;
			}
			// ������ ���ʿ� �н��� ���
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

	// �� �÷��̾� �� �� �÷��̾ ���� ���� �޼��� ���
	if( CurrentPlayer.GetPassNumber() >= 3 ||
		CurrentPlayer.GetStoneNumber() <= 0 )
	{
		Man.UpdateBoard( CurrentPlayer, GameRound, Board );
		Man.UpdateBoard( OtherPlayer, GameRound, Board );
		GameRound++;
		ComposeFrame();
		return;
	}

	// �÷��̾� ���ۿ� ���� Target ��ġ ����
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
	// �н� ���� ���
	else if( Input == 'P' || Input == 'p' )
	{
		CurrentPlayer.IncreasePassNumber();
		// ��ŵ�� ��� ���� ��ġ�� (-1,-1)�� �־� ���Ŀ� ������ �� �ֵ��� ��.
		CurrentPlayer.PutStoneForReplay( -1, -1 );
		GameRound++;
	}
	// �ٵ��� �α�� ������ ���
	else if( Input == 'O' || Input == 'o' )
	{
		if( Man.PutStone( TargetX, TargetY, CurrentPlayer, GameRound, Board ) )
		{
			CurrentPlayer.DeacreaseStoneNumber();
			// ���⸦ ���� ���Ϳ� �ٵϵ� ���� ��ġ ����
			CurrentPlayer.PutStoneForReplay( TargetX, TargetY );
			Man.UpdateBoard( OtherPlayer, GameRound, Board );
			GameRound++;
		}
	}
	else
	{
		Man.InputException( ReplayRound );
	}

	// ���� ���� ���� Ȯ��
	// 1. �� �÷��̾ ��� 2�� �̻� �н��� ���
	if( CurrentPlayer.GetPassNumber() >= 3 &&
		OtherPlayer.GetPassNumber() >= 3 )
	{
		EndRound = true;
	}
	// 2. �� �÷��̾ �ٵϵ��� ��� ������ ���
	if( CurrentPlayer.GetStoneNumber() <= 0 &&
		OtherPlayer.GetStoneNumber() <= 0 )
	{
		EndRound = true;
	}

	// ���� ������ ��� ȣ��
	if( Input != ' ' )
	{
		// ����ڷ� ���� �Է��� ������ ���� �������� ���� �׸����� ��.
		// �Է��� ���� ���� ����ؼ� �׸� ���, ȭ�� �������� �� ���� �߻���.
		ComposeFrame();
	}
}

void Game::ComposeFrame()
{
	system( "cls" );
	if( StartRound )
	{
		/*
			< ���� �ʱ� ���� ��Ȳ. ���� ȭ�� ���>
			StartScreen() �Լ� ȣ���� ����ȭ�� ����ϰ�,
			Update() �Լ����� �Է� üũ �������� ���� �ٵ��� ȭ������ �ٷ�
			�Ѿ�� �ʱ� ������, �߰������� �� �κп��� ȭ�� �ʱ�ȭ ��
			�ٵ��� ��� �Լ��� �����Ͽ���.
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
