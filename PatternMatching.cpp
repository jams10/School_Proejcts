#include <iostream>
#include <string>
#include <windows.h>
#include <conio.h>

enum MODE
{
    QUIT = 0,
    ENTER_STRING,
    ENTER_PATTERN,
    PATTERN_MATCHING,
};

void Match( std::string pattern, std::string string, int patternLength, int stringLength );

int main()
{
    std::string s = "";
    std::string pattern = "";
    bool loop = true;

    while( loop )
    {
        system( "cls" );

        std::cout << " < 작업을 선택하세요 > " << std::endl << std::endl;
        std::cout << " 1 : 패턴 매칭 대상 문자열 입력 " << std::endl;
        std::cout << " 2 : 패턴 문자열 입력 " << std::endl;
        std::cout << " 3 : 패턴 매칭 수행 " << std::endl;
        std::cout << " 0 : 종료 " << std::endl << std::endl;
        std::cout << ">> ";

        int input = _getch() - '0';

        switch( input )
        {
        case ENTER_STRING:
            std::cout << "문자열을 입력하세요 : ";
            std::cin >> s;
            break;
        case ENTER_PATTERN:
            std::cout << "문자열을 입력하세요 : ";
            std::cin >> pattern;
            break;
        case PATTERN_MATCHING:
            if( s == "" || pattern == "" )
            {
                std::cout << "패턴 대상 문자열 및 패턴 문자열을 먼저 입력해주세요..." << std::endl;
                Sleep( 2000 );
                continue;
            }
            system( "cls" );
            std::cout << "현재 문자열 : " << s << std::endl;
            std::cout << "현재 패턴   : " << pattern << std::endl;
            Match( pattern, " " + s, pattern.length(), s.length());
            Sleep( 3000 );
            break;
        case QUIT:
            std::cout << "프로그램을 종료합니다..." << std::endl;
            Sleep( 1000 );
            loop = false;
            break;
        default:
            std::cout << "0 ~ 3 까지의 숫자를 입력해주세요..." << std::endl;
            Sleep( 2000 );
        }
    }

    return 0;
}

void Match( std::string pattern, std::string string, int patternLength, int stringLength )
{
    int stringIndex = 0;
    bool matched = false;

    while( stringIndex <= stringLength - patternLength + 1 && !matched )
    {
        ++stringIndex;
        int patternIndex = 0;
        matched = true;
        while( patternIndex < patternLength && matched )
        {
            matched = matched && (pattern[patternIndex] == string[stringIndex  + patternIndex]);
            ++patternIndex;
        }
    }
    std::cout << std::endl;
    if( stringIndex <= stringLength - patternLength + 1 )
    {
        std::cout << "패턴 찾음! 패턴은 주어진 문자열 인덱스 [" << stringIndex - 1 <<"] 에 위치합니다." << std::endl;
    }
    else
    {
        std::cout << "패턴을 찾을 수 없습니다... " << std::endl;
    }
}