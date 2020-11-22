#pragma once

#include "Board.h"
#include "Stone.h"
#include "Player.h"
#include "Vec2.h"

enum Condition
{
	NOTHING,
	OVER_SKIP_COUNTS,   // 스킵 횟수 초과
	INPUT_EXCEPTION,    // 입력 예외
	BLACK_PUT_STONE,    // 처음 흑돌 가장자리 조건
	PUT_ERROR,          // 바둑돌 둘 수 없음
	ETC
};

class Game
{
	Board board;       // 바둑판 인스턴스
	bool gameStart;    // 게임 시작 여부
	bool gameEnd;      // 게임 종료 여부
	int round;         // 게임 라운드
	int cond;          // 기타 게임 상태
	Vec2 currentPos;   // 현재 위치
	Player players[2]; // 플레이어 인스턴스
public:
	Game();
	void Go();           // 게임 실행
	void Update();       // 게임 업데이트
	void Compose();      // 게임 화면 출력
	void PrintState();   // 차례 및 점수 등 출력
	void Notification(); // 기타 상태 알림 출력 함수
};