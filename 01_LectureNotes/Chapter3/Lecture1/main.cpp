#include "Game2D.h"
#include "Examples/PrimitivesGallery.h"
#include "RandomNumberGenerator.h"
#include <vector>
#include <memory>

namespace jm
{
	class RigidCircle
	{
	public:
		vec2 pos;
		vec2 vel;
		float radius = 0.1f;

		void draw()
		{
			beginTransformation();
			{
				translate(pos);
				drawFilledCircle(Colors::hotpink, radius - 1e-3f);
				setLineWidth(2.0f);
				drawWiredCircle(Colors::black, radius);
			}
			endTransformation();
		}

		void update(const float & dt)
		{
			/* numerical integration
			- 눈금 한 칸에 0.5m이다.
			- 가속도는 속도를, 속도는 위치를 변화시킨다.
			- Newton's_2nd_law.JPG, Finite_Difference_Method.JPG 참고
			*/
			static const vec2 gravity = vec2(0.0f, -9.81f);
			vel += gravity * dt;

			// 위의 gravity를 고려하지 않으면(=주석 처리하면) 직진만 한다. 
			pos += vel * dt;

			// wall collision
			static const float coef_rest = 0.7f; // Coefficient of restitution(반발 계수)
			static const float coef_fric = 0.98f;

			if (1.0f - pos.x <= radius) // right wall
			{
				pos.x = 1.0f - radius;

				if (vel.x >= 0.0f) // 안전 장치
					vel.x *= -1.0f * coef_rest;
			}

			if (pos.x <= -1.0f + radius) // left wall
			{
				pos.x = -1.0f + radius;

				if (vel.x <= 0.0f)
					vel.x *= -1.0f * coef_rest;
			}

			if (pos.y <= - 1.0f + radius) // ground
			{
				pos.y = -1.0f + radius;

				if (vel.x <= 0.0f)
					vel.y *= -1.0f * coef_rest;

				// friction (not pysical)
				vel.x *= coef_fric;
			}
		}
	};

	class Example : public Game2D
	{
	public:
		RigidCircle rigid_body;

		Example()
			: Game2D()
		{
			reset();
		}

		void reset()
		{
			// Initial position and velocity
			rigid_body.pos = vec2(-0.8f, 0.3f);
			rigid_body.vel = vec2(15.0f, 0.0f);
		}

		void drawWall()
		{
			setLineWidth(5.0f);
			drawLine(Colors::blue, { -1.0f, -1.0f }, Colors::blue, { 1.0f, -1.0f });
			drawLine(Colors::blue, { 1.0f, -1.0f }, Colors::blue, { 1.0f, 1.0f });
			drawLine(Colors::blue, { -1.0f, -1.0f }, Colors::blue, { -1.0f, 1.0f });
		}

		void update() override
		{
			// physics update
			rigid_body.update(getTimeStep() * 0.1f); // 현실은 1.0f -> 10분의 1로 단축.

			// draw
			drawWall();
			rigid_body.draw();

			// reset button
			if (isKeyPressedAndReleased(GLFW_KEY_R)) reset();
		}
	};
}

int main(void)
{
	jm::Example().run();

	return 0;
}
