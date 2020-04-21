#pragma once
#include "GeometricObject.h"

namespace jm
{
	class Square : public GeometricObject
	{
	public:
		void draw()
		{
			beginTransformation();
			{
				translate(pos);
				drawFilledSquare(color, size);
			}
			endTransformation();
		}
	};
}