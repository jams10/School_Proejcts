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
    // �÷��̾� ����
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
    std::cout << "������ �����մϴ�..." << std::endl << std::endl;
    Sleep( 1000 );
}

void Game::Update()
{
    char input = ' ';
    bool isValid = true;
    
    // ����� �Է� �ް� Ȯ��
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
    // Q �Ǵ� q �Է½� ����
    else if( input == 'Q' || input == 'q' )
    {
        gameEnd = true;
    }
    // P �Ǵ� p �Է½� ���� ��ŵ
    else if( input == 'P' || input == 'p' )
    {
        // �÷��̾�� 2ȸ �̻� ��ŵ �Ұ���
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
    // O �Ǵ� o �Է½� �ٵϵ� ����
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
                round++; // �ٵϵ� ���ƾ߸� ���� ���ʷ� �Ѿ
            }
        }
        else
        {
            board.PutStone( currentPos, players[round % 2], isValid );
            round++; // �ٵϵ� ���ƾ߸� ���� ���ʷ� �Ѿ
        }
        if( !isValid )
        {
            cond = Condition::PUT_ERROR;
            round--;
        }
    }
    // ���� �Է� ó��
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
    std::cout << "���� ���� : ";
    if( round % 2 == 0 ) std::cout << "��";
    else std::cout << "��";
    std::cout << round << std::endl;
    std::cout << std::endl << std::endl;
}

void Game::Notification()
{
    switch( cond )
    {
    case OVER_SKIP_COUNTS:
        std::cout << "�̹� 2ȸ ��ŵ�Ͽ����ϴ�." << std::endl;
        break;
    case INPUT_EXCEPTION:
        std::cout << "�߸��� �Է��Դϴ�." << std::endl;
        break;
    case BLACK_PUT_STONE:
        std::cout << "ó�� �浹�� �����ڸ����� �� �� �ֽ��ϴ�." << std::endl;
        break;
    case PUT_ERROR:
        std::cout << "�ش� ��ġ���� ���� �� �� �����ϴ�." << std::endl;
    default:
        break;
    }
    cond = Condition::NOTHING;
}

