#include "Game2D.h"
#include "Examples/PrimitivesGallery.h"
#include "RandomNumberGenerator.h"
#include "RigidCircle.h"
#include <vector>
#include <memory>

// normal 방향만 고려하였으며 접선 방향(회전하며 부딪치는 두 물체)은 고려하지 않음.

namespace jm
{
	class Example : public Game2D
	{
	public:
		RigidCircle rb0, rb1; // rigid body

		Example()
			: Game2D()
		{
			reset();
		}

		void reset()
		{
			// Initial position and velocity
			rb0.pos = vec2(-0.8f, 0.2f);
			rb0.vel = vec2(5.0f, 0.0f);
			rb0.color = Colors::hotpink;
			rb0.radius = 0.1f;
			rb0.mass = 1.0f;

			rb1.pos = vec2(0.8f, 0.3f);
			rb1.vel = vec2(-5.0f, 0.0f);
			rb1.color = Colors::yellow;
			rb1.radius = 0.12f;
			rb1.mass = rb0.mass * std::pow(rb1.radius / rb0.radius, 2.0f);
			// : rb1의 mass는 rb0와 같은 밀도이며 넓이와 비례하도록; 3차원이라면 3.0f임.
		}

		void drawWall()
		{
			setLineWidth(5.0f);
			drawLine(Colors::blue, { -1.0f, -1.0f }, Colors::blue, { 1.0f, -1.0f });
			drawLine(Colors::blue, { 1.0f, -1.0f }, Colors::blue, { 1.0f, 1.0f });
			drawLine(Colors::blue, { -1.0f, -1.0f }, Colors::blue, { -1.0f, 1.0f });
		}

		float dot(vec2 A, vec2 B)
		{
			float result = (A.x * B.x) + (A.y * B.y);

			return result;
		}

		void update() override
		{
			const float dt = getTimeStep() * 0.4f;
			const float epsilon = 0.5f;

			// physics update
			rb0.update(dt);
			rb1.update(dt);

			/* 
			const float norm = sqrt(std::pow(rb0.pos.x - rb1.pos.x, 2.0f)
				+ std::pow(rb0.pos.y - rb1.pos.y, 2.0f));
			*/
			const float distance = (rb0.pos - rb1.pos).getMagnitude();

			// check collision between two rigid bodies
			if (distance <= rb0.radius + rb1.radius)
			{
				// compute impulse
				const auto vel_rel = rb0.vel - rb1.vel;
				const auto normal = -(rb1.pos - rb0.pos) / (rb1.pos - rb0.pos).getMagnitude();

				if (vel_rel.getDotProduct(normal) < 0.0f) // approaching
				{
					/*
					rb0.n = (rb1.pos - rb0.pos) / distance;
					rb1.n = -rb0.n;

					float j = -(1.0f + epsilon) * dot((rb0.vel - rb1.vel), rb1.n)
						/ (1.0f / rb0.mass + 1.0f / rb1.mass);

					rb0.vel += rb1.n * j / rb0.mass;
					rb1.vel -= rb1.n * j / rb1.mass;
					*/

					const auto impulse = normal * -(1.0f + epsilon)
						* vel_rel.getDotProduct(normal)
						/ (1.0f / rb0.mass + 1.0f / rb1.mass);
					
					// update velocities of two bodies
					rb0.vel += impulse / rb0.mass;
					rb1.vel -= impulse / rb1.mass;
				}
			}

			// draw
			drawWall();
			rb0.draw();
			rb1.draw();

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
