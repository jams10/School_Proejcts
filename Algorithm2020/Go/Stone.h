#pragma once

#include <string>
#include "Vec2.h"

class Stone
{
public:
	Vec2 pos;           // ¹ÙµÏ¾Ë À§Ä¡
	std::string color;  // ¹ÙµÏ¾Ë »ö±ò
public:
	Stone() = default;
	Stone( const Vec2& pos, const std::string& color );
};