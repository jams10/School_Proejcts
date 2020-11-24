#include <iostream>
#include <Windows.h>
#include <conio.h>
#include "Graph.h"

enum Menu
{
    SHOW_CONNECTIONS = 1,
    SET_CONNECTION,
    BRIDGE_TEST,
    SHOW_BRIDGE,
    END,
    EXCEPTION
};

#define OUT

int main()
{
    int n = 0;
    std::cout << "꼭짓점 개수를 입력해주세요 : ";
    std::cin >> n;

    Graph g( n );

    int select = 0;
    while( true )
    {
        system( "cls" );
        std::cout << std::endl;
        std::cout << "---------------Graph Program---------------" << std::endl << std::endl;
        std::cout << "1. 그래프 연결 상태" << std::endl;
        std::cout << "2. 꼭짓점 연결" << std::endl;
        std::cout << "3. 브릿지 테스트" << std::endl;
        std::cout << "4. 전체 브릿지 출력" << std::endl;
        std::cout << "5. 종료" << std::endl;
        std::cout << "메뉴를 선택해주세요(숫자) : ";
        select = _getch() - '0';

        if( SHOW_CONNECTIONS > select || END < select )
        {
            std::cout << "잘못된 숫자를 입력하셨습니다." << std::endl;
            system( "pause" );
            continue;
        }
        else if( select == END )
        {
            system( "cls" );
            std::cout << "프로그램을 종료합니다..." << std::endl;
            Sleep( 2000 );
            break;
        }
        
        int v1 = 0, v2 = 0;

        switch( select )
        {
        case SHOW_CONNECTIONS:
            system( "cls" );
            std::cout << "---------------Graph Program---------------" << std::endl << std::endl;
            std::cout << "그래프 연결 상태" << std::endl << std::endl;
            g.ShowConnections();
            system( "pause" );
            break;
        case SET_CONNECTION:
            system( "cls" );
            std::cout << "---------------Graph Program---------------" << std::endl << std::endl;
            std::cout << "그래프 연결 설정" << std::endl << std::endl;
            std::cout << "서로 연결할 꼭짓점을 입력해 주세요 : ";
            std::cin >> v1 >> v2;
            if( !g.SetConnection( v1, v2 ) )
            {
                system( "pause" );
            }
            break;
        case BRIDGE_TEST:
            system( "cls" );
            std::cout << "---------------Graph Program---------------" << std::endl << std::endl;
            std::cout << "그래프 브릿지 테스트" << std::endl << std::endl;
            std::cout << "테스트할 간선의 양 끝점을 입력해 주세요 : ";
            std::cin >> v1 >> v2;
            if( g.IsBridge( v1, v2 ) )
            {
                std::cout << "해당 간선은 브릿지 입니다." << std::endl;
            }
            else std::cout << "해당 간선은 브릿지가 아닙니다." << std::endl;
            system( "pause" );
            break;
        case SHOW_BRIDGE:
            system( "cls" );
            std::cout << "---------------Graph Program---------------" << std::endl << std::endl;
            std::cout << "그래프의 전체 브릿지" << std::endl << std::endl;
            g.ShowBridges();
            system( "pause" );
            break;
        default:
            break;
        }
    }
    return 0;
}

