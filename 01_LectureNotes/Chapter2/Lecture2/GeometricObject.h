#pragma once
#include "Game2D.h"

namespace jm
{
	class GeometricObject
	{
	public:
		vec2 pos;
		RGB color;
		float size;

		void init(const vec2 & _pos, const RGB & _color, const float & _size)
		{
			pos = _pos;
			color = _color;
			size = _size;
		}
	};
}