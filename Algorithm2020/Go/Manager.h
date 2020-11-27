#pragma once

#include "Board.h"
#include "Player.h"

class Manager
{
public:
	Manager();

	/* 출력 함수들 */
	void PrintOffSetY( const int& OffSet ) const;				 
	void PrintOffSetX( const int& OffSet ) const;
	void PrintGameScreen( const int& TargetX, const int& TatgetY,      // 게임 화면 출력
		                  const int& GameRound, const Player Players[], const Board& Board ) const;
	void PrintError();
	void PrintReplayInfo( const Player& Player, const int& GameRound, const bool& HasPass ) const;
	bool PrintGameResult( const Player Players[], const Board& Board ) const;
	
	// 게임 시작 화면 ( 바둑판 크기 및 플레이어 초기 설정 )
	void StartScreen( Player Players[], Board& Board );

	// 해당 바둑판 공간 검사 함수
	bool IsValidSpace( const int& TargetX, const int& TargetY, const int& GameRound, Board& Board );
	
	// 바둑알 놓는 작업 처리 함수
	bool PutStone( const int& TargetX, const int& TargetY,
		           const Player& Player, const int& GameRound, Board& Board );
	
	// 패 위치 색상 체크 함수
	std::string KoCheck( const int& X, const int& Y, const Board& Board );
	
	// 바둑판 업데이트
	void UpdateBoard( const Player& Player, const int& GameRound, Board& Board );

	// 패 위치 리셋
	void ResetKo( Board& Board );

	// 입력 예외 처리
	void InputException( const bool& ReplayRound );

	// 점수 계산
	void CalcScore( Player Players[], Board& Board ) const;
private:
	/* Print Offset */
	int HeightOffSet = 5;
	int WidthOffSet = 15;
	// 에러 메시지
	std::string ERROR_MSG = " ";
	std::vector<Position> Kos;
	// 에러 발생 여부 확인 플래그
	bool ErrorHasOccured = false;
};