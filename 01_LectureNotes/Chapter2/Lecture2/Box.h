#pragma once
#include "GeometricObject.h"

namespace jm
{
	class Box : public GeometricObject
	{
	public:
		float width, height;

		void init(const vec2 & _pos, const RGB & _color, const float & _angle,
			const float & _width, const float & _height)
		{
			GeometricObject::init(_pos, _color, _angle);
			width = _width;
			height = _height;
		}
		
		void drawGeometric() const override
		{
			drawFilledBox(GeometricObject::color, this->width, this->height);
			/* 부모 class에서 상속받았다는 것을 명확하게 표시하고 싶다면,
			   size = GeometricObject::size */
		}
	};
}