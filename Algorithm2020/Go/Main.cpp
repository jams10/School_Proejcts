#include <iostream>
#include <Windows.h>
#include "Game.h"

int main()
{
	Game game;
	game.Go();

	std::cout << "프로그램을 종료합니다...";
	Sleep( 2000 );

	return 0;
}