#pragma once
#include "GeometricObject.h"

namespace jm
{
	class Pentagon : public GeometricObject
	{
	public:
		void draw()
		{
			beginTransformation();
			{
				translate(pos);
				drawFilledPentagon(color, size);
			}
			endTransformation();
		}
	};
}