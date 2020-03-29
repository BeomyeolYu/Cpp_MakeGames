#pragma once

#include "Game2D.h"

namespace jm
{
	class MyTank
	{
	public:
		vec2 center = vec2(0.0f, 0.0f);
		//vec2 direction = vec2(1.0f, 0.0f, 0.0f);
		int numBullet = 0;

		void draw()
		{
			beginTransformation();
			{
				translate(center);
				drawFilledBox(Colors::green, 0.25f, 0.1f); // body
				translate(-0.02f, 0.1f);
				drawFilledBox(Colors::blue, 0.15f, 0.09f); // turret
				translate(0.15f, 0.0f);
				drawFilledBox(Colors::red, 0.15f, 0.03f);  // barrel
			}
			endTransformation();
		}
	};

	class MyBullet
	{
	public:
		vec2 center = vec2(0.0f, 0.0f);
		vec2 velocity = vec2(0.0f, 0.0f);
		
		void draw()
		{
			beginTransformation();
			translate(center);
			drawFilledRegularConvexPolygon(Colors::yellow, 0.02f, 8);
			drawWiredRegularConvexPolygon(Colors::gray, 0.02f, 8);
			endTransformation();
		}

		void update(const float& dt)
		{
			center += velocity * dt;
		}
	};

	class TankExample : public Game2D
	{
	public:
		MyTank tank;

		MyBullet* bullet[10] = { nullptr, nullptr, nullptr, nullptr, nullptr
		, nullptr , nullptr , nullptr , nullptr , nullptr };
		//TODO: allow multiple bullets
		//TODO: delete bullets when they go out of the screen
		
	public:
		TankExample()
			: Game2D("This is my digital canvas!", 1024, 768, false, 2)
		{}

		~TankExample() // bullet = new MyBullet; 이후에 메모리 누수를 방지하기 위한 소멸자.
		{
			if (bullet[0] != nullptr) delete bullet[0];
			if (bullet[1] != nullptr) delete bullet[1];
			if (bullet[2] != nullptr) delete bullet[2];
			if (bullet[3] != nullptr) delete bullet[3];
			if (bullet[4] != nullptr) delete bullet[4];
			if (bullet[5] != nullptr) delete bullet[5];
			if (bullet[6] != nullptr) delete bullet[6];
			if (bullet[7] != nullptr) delete bullet[7];
			if (bullet[8] != nullptr) delete bullet[8];
			if (bullet[9] != nullptr) delete bullet[9];
		}
		
		void update() override
		{
			// move tank
			if (isKeyPressed(GLFW_KEY_LEFT))	tank.center.x -= 0.5f * getTimeStep();
			if (isKeyPressed(GLFW_KEY_RIGHT))	tank.center.x += 0.5f * getTimeStep();
			if (isKeyPressed(GLFW_KEY_UP))		tank.center.y += 0.5f * getTimeStep();
			if (isKeyPressed(GLFW_KEY_DOWN))	tank.center.y -= 0.5f * getTimeStep();

			// shoot a cannon ball
			if (isKeyPressedAndReleased(GLFW_KEY_SPACE))
			{
				bullet[tank.numBullet] = new MyBullet;
				bullet[tank.numBullet]->center = tank.center;
				bullet[tank.numBullet]->center.x += 0.2f;
				bullet[tank.numBullet]->center.y += 0.1f;
				bullet[tank.numBullet]->velocity = vec2(2.0f, 0.0f);

				//std::cout << tank.numBullet << std::endl;
				//std::cout << bullet[tank.numBullet] << std::endl;
				tank.numBullet += 1;

				if (tank.numBullet == 9)  tank.numBullet = 0;
			}

			// if (bullet != nullptr) = bullet이 없는 경우 발생하는 런타임 에러 방지.
			if (bullet[0] != nullptr) bullet[0]->update(getTimeStep());
			if (bullet[1] != nullptr) bullet[1]->update(getTimeStep());
			if (bullet[2] != nullptr) bullet[2]->update(getTimeStep());
			if (bullet[3] != nullptr) bullet[3]->update(getTimeStep());
			if (bullet[4] != nullptr) bullet[4]->update(getTimeStep());
			if (bullet[5] != nullptr) bullet[5]->update(getTimeStep());
			if (bullet[6] != nullptr) bullet[6]->update(getTimeStep());
			if (bullet[7] != nullptr) bullet[7]->update(getTimeStep());
			if (bullet[8] != nullptr) bullet[8]->update(getTimeStep());
			if (bullet[9] != nullptr) bullet[9]->update(getTimeStep());

			// rendering
			tank.draw();

			if (bullet[0] != nullptr) bullet[0]->draw();
			if (bullet[1] != nullptr) bullet[1]->draw();
			if (bullet[2] != nullptr) bullet[2]->draw();
			if (bullet[3] != nullptr) bullet[3]->draw();
			if (bullet[4] != nullptr) bullet[4]->draw();
			if (bullet[5] != nullptr) bullet[5]->draw();
			if (bullet[6] != nullptr) bullet[6]->draw();
			if (bullet[7] != nullptr) bullet[7]->draw();
			if (bullet[8] != nullptr) bullet[8]->draw();
			if (bullet[9] != nullptr) bullet[9]->draw();
		}
	};
}