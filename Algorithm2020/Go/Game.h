#pragma once

#include "Board.h"
#include "Player.h"
#include "Manager.h"

class Game
{
public:
	Game();
	// 게임 실행 함수
	void Go();
private:
	// 매 프레임 마다 게임 상태를 갱신해주는 함수
	void Update();
	// 매 프레임 마다 게임 화면 출력해주는 함수
	void ComposeFrame();
public:
	Position ReplayPos;
private:
	// 현재 위치
	int TargetX = 0;
	int TargetY = 0;
	// 게임 라운드
	int GameRound = 0;
	// 게임 단계( 시작 - 종료 - 복기 순)
	bool StartRound = true;
	bool EndRound = false;
	bool ReplayRound = false;
	/* 복기 모드에서 사용 */
	bool HasPass = false;
	Player CurPlayer;

	// 플레이어 배열
	Player Players[2];
	// 바둑판 인스턴스
	Board Board;
	// 게임 매니저 인스턴스
	Manager Man;
};