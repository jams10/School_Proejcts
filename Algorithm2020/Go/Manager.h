#pragma once

#include "Board.h"
#include "Player.h"

class Manager
{
public:
	Manager();

	/* ��� �Լ��� */
	void PrintOffSetY( const int& OffSet ) const;				 
	void PrintOffSetX( const int& OffSet ) const;
	void PrintGameScreen( const int& TargetX, const int& TatgetY,      // ���� ȭ�� ���
		                  const int& GameRound, const Player Players[], const Board& Board ) const;
	void PrintError();
	void PrintReplayInfo( const Player& Player, const int& GameRound, const bool& HasPass ) const;
	bool PrintGameResult( const Player Players[], const Board& Board ) const;
	
	// ���� ���� ȭ�� ( �ٵ��� ũ�� �� �÷��̾� �ʱ� ���� )
	void StartScreen( Player Players[], Board& Board );

	// �ش� �ٵ��� ���� �˻� �Լ�
	bool IsValidSpace( const int& TargetX, const int& TargetY, const int& GameRound, Board& Board );
	
	// �ٵϾ� ���� �۾� ó�� �Լ�
	bool PutStone( const int& TargetX, const int& TargetY,
		           const Player& Player, const int& GameRound, Board& Board );
	
	// �� ��ġ ���� üũ �Լ�
	std::string KoCheck( const int& X, const int& Y, const Board& Board );
	
	// �ٵ��� ������Ʈ
	void UpdateBoard( const Player& Player, const int& GameRound, Board& Board );

	// �� ��ġ ����
	void ResetKo( Board& Board );

	// �Է� ���� ó��
	void InputException( const bool& ReplayRound );

	// ���� ���
	void CalcScore( Player Players[], Board& Board ) const;
private:
	/* Print Offset */
	int HeightOffSet = 5;
	int WidthOffSet = 15;
	// ���� �޽���
	std::string ERROR_MSG = " ";
	std::vector<Position> Kos;
	// ���� �߻� ���� Ȯ�� �÷���
	bool ErrorHasOccured = false;
};