#pragma once

#include <string>
#include "Vec2.h"

class Stone
{
public:
	Vec2 pos;           // �ٵϾ� ��ġ
	std::string color;  // �ٵϾ� ����
public:
	Stone() = default;
	Stone( const Vec2& pos, const std::string& color );
};