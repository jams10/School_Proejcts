#pragma once

#include <string>
#include "Icon.h"

class Position
{
public:
	Position() = default;
	Position( const int& x, const int& y );
public:
	int x = 0;
	int y = 0;
	std::string Stone = EMPTY;
	bool IsKo = false;
};