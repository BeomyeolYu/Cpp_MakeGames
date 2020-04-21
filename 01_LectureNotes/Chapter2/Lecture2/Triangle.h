#pragma once
#include "Game2D.h"

namespace jm
{
	class Triangle
	{
	public:
		vec2 pos = vec2{ -0.5f, -0.05f };
		RGB color = Colors::yellow;
		float size = 0.3f;

		void draw()
		{
			beginTransformation();
			{
				translate(pos);
				drawFilledTriangle(color, size);
			}
			endTransformation();
		}
	};
}
