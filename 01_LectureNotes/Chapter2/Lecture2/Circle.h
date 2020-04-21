#pragma once
#include "Game2D.h"

namespace jm
{
	class Circle
	{
	public:
		vec2 pos = vec2{ 0.0f, 0.0f };
		RGB color = Colors::yellow;
		float size = 0.15f;

		void draw()
		{
			beginTransformation();
			{
				translate(pos);
				drawFilledCircle(color, size);
			}
			endTransformation();
		}
	};
}
