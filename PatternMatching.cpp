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

        std::cout << " < �۾��� �����ϼ��� > " << std::endl << std::endl;
        std::cout << " 1 : ���� ��Ī ��� ���ڿ� �Է� " << std::endl;
        std::cout << " 2 : ���� ���ڿ� �Է� " << std::endl;
        std::cout << " 3 : ���� ��Ī ���� " << std::endl;
        std::cout << " 0 : ���� " << std::endl << std::endl;
        std::cout << ">> ";

        int input = _getch() - '0';

        switch( input )
        {
        case ENTER_STRING:
            std::cout << "���ڿ��� �Է��ϼ��� : ";
            std::cin >> s;
            break;
        case ENTER_PATTERN:
            std::cout << "���ڿ��� �Է��ϼ��� : ";
            std::cin >> pattern;
            break;
        case PATTERN_MATCHING:
            if( s == "" || pattern == "" )
            {
                std::cout << "���� ��� ���ڿ� �� ���� ���ڿ��� ���� �Է����ּ���..." << std::endl;
                Sleep( 2000 );
                continue;
            }
            system( "cls" );
            std::cout << "���� ���ڿ� : " << s << std::endl;
            std::cout << "���� ����   : " << pattern << std::endl;
            Match( pattern, " " + s, pattern.length(), s.length());
            Sleep( 3000 );
            break;
        case QUIT:
            std::cout << "���α׷��� �����մϴ�..." << std::endl;
            Sleep( 1000 );
            loop = false;
            break;
        default:
            std::cout << "0 ~ 3 ������ ���ڸ� �Է����ּ���..." << std::endl;
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
        std::cout << "���� ã��! ������ �־��� ���ڿ� �ε��� [" << stringIndex - 1 <<"] �� ��ġ�մϴ�." << std::endl;
    }
    else
    {
        std::cout << "������ ã�� �� �����ϴ�... " << std::endl;
    }
}