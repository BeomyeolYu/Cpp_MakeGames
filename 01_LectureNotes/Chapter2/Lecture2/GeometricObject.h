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

		/* �ڽ� class���� ����� ������ �����Ƿ� �θ� class������ ������ �ִ� ô�� �Ѵ�.
		
		void drawGeometric()
		{
			// XXXX
		}
		*/

		/* virtual�� �ٿ����� ������ �ڽ� class�� drawGeometry()�� �ҷ����� ���Ѵ�.
		  - ������� ���α׷���(1): �θ� class�� const, �ڽ� class�� const override�� �ٿ��ش�. 
		
		virtual void drawGeometric() const
		{
			// XXXX
		}
		 */

		/* ������� ���α׷���(2): ���� ���� �Լ�(pure virtual function)�� �̿��ϸ�,
		�ڽ� class�� void drawGeometric() const override�� ���� �� ������ �߻��Ѵ�.
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
