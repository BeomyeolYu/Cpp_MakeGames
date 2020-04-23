#pragma once
#include "Game2D.h"

namespace jm
{
	class GeometricObject
	{
	public:
		vec2 pos;
		RGB color;
		float ang;

		void init(const vec2 & _pos, const RGB & _color, const float & _angle)
		{
			pos = _pos;
			color = _color;
			ang = _angle;
		}

		/* 자식 class에서 기능을 가지고 있으므로 부모 class에서는 가지고 있는 척만 한다.
		
		void drawGeometric()
		{
			// XXXX
		}
		*/

		/* virtual을 붙여주지 않으면 자식 class의 drawGeometry()을 불러오지 못한다.
		  - 방어적인 프로그래밍(1): 부모 class에 const, 자식 class에 const override를 붙여준다. 
		
		virtual void drawGeometric() const
		{
			// XXXX
		}
		 */

		/* 방어적인 프로그래밍(2): 순수 가상 함수(pure virtual function)를 이용하면,
		자식 class에 void drawGeometric() const override가 없을 시 오류가 발생한다.
		*/
		virtual void drawGeometric() const = 0;

		void draw()
		{
			beginTransformation();
			{
				translate(pos);
				rotate(ang);
				drawGeometric();
			}
			endTransformation();
		}
	};
}
