#pragma once
#include "GeometricObject.h"

namespace jm
{
	class Square : public GeometricObject
	{
	public:
		float size;

		void init(const vec2 & _pos, const RGB & _color, const float & _angle,
			const float & _size)
		{
			GeometricObject::init(_pos, _color, _angle);
			size = _size;
		}

		void drawGeometric() const override
		{
			drawFilledSquare(GeometricObject::color, size);
		}
	};
}