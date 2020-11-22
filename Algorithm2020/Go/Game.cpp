#include <iostream>
#include <Windows.h>
#include <conio.h>
#include "Game.h"

Game::Game()
    :
    gameStart( true ),
    gameEnd( false ),
    round( 0 ),
    cond( Condition::NOTHING )
{
    currentPos = Vec2( 3, 3 );
    // 플레이어 생성
    for( int i = 0; i < 2; ++i )
    {
        players[i] = Player( i );
    }
}

void Game::Go()
{
    while( !gameEnd )
    {
        if(gameStart) Compose();
        Update();
    }
    std::cout << "게임을 종료합니다..." << std::endl << std::endl;
    Sleep( 1000 );
}

void Game::Update()
{
    char input = ' ';
    bool isValid = true;
    
    // 사용자 입력 받고 확인
    input = _getch();
    // WASD
    if( input == 'W' || input == 'w' )
    {
        if( currentPos.y - 1 >= 0 ) currentPos.y--;
    }
    else if( input == 'S' || input == 's' )
    {
        if( currentPos.y - 1 < 8 ) currentPos.y++;
    }
    else if( input == 'A' || input == 'a' )
    {
        if( currentPos.x - 1 >= 0 ) currentPos.x--;
    }
    else if( input == 'D' || input == 'd' )
    {
        if( currentPos.x + 1 < 8 ) currentPos.x++;
    }
    // Q 또는 q 입력시 종료
    else if( input == 'Q' || input == 'q' )
    {
        gameEnd = true;
    }
    // P 또는 p 입력시 차례 스킵
    else if( input == 'P' || input == 'p' )
    {
        // 플레이어는 2회 이상 스킵 불가능
        if( players[round % 2].skip >= 2 )
        {
            cond = Condition::OVER_SKIP_COUNTS;
        }
        else
        {
            players[round % 2].skip++;
            board.Skip( players[round % 2] );
            round++;
        }
    }
    // O 또는 o 입력시 바둑돌 놓기
    else if( input == 'O' || input == 'o' )
    {
        if( round == 0 )
        {
            if( currentPos.x > 0 && currentPos.x < 7 &&
                currentPos.y > 0 && currentPos.y < 7 )
            {
                cond = Condition::BLACK_PUT_STONE;
            }
            else
            {
                board.PutStone( currentPos, players[round % 2], isValid );
                round++; // 바둑돌 놓아야만 다음 차례로 넘어감
            }
        }
        else
        {
            board.PutStone( currentPos, players[round % 2], isValid );
            round++; // 바둑돌 놓아야만 다음 차례로 넘어감
        }
        if( !isValid )
        {
            cond = Condition::PUT_ERROR;
            round--;
        }
    }
    // 예외 입력 처리
    else
    {
        cond = Condition::INPUT_EXCEPTION;
    }
    
    Compose();
}

void Game::Compose()
{
    system( "cls" );
    if( gameStart )
    {
        gameStart = false;
    }
    if( !gameEnd )
    {
        PrintState();
        board.Print(currentPos, round);
        Notification();
    }
}

void Game::PrintState()
{
    std::cout << "현재 차례 : ";
    if( round % 2 == 0 ) std::cout << "흑";
    else std::cout << "백";
    std::cout << round << std::endl;
    std::cout << std::endl << std::endl;
}

void Game::Notification()
{
    switch( cond )
    {
    case OVER_SKIP_COUNTS:
        std::cout << "이미 2회 스킵하였습니다." << std::endl;
        break;
    case INPUT_EXCEPTION:
        std::cout << "잘못된 입력입니다." << std::endl;
        break;
    case BLACK_PUT_STONE:
        std::cout << "처음 흑돌은 가장자리에만 둘 수 있습니다." << std::endl;
        break;
    case PUT_ERROR:
        std::cout << "해당 위치에는 돌을 둘 수 없습니다." << std::endl;
    default:
        break;
    }
    cond = Condition::NOTHING;
}

