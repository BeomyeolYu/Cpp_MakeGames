#pragma once

#include "Game2D.h"

namespace jm
{
	/*
	TODO:
	- add left arm and left leg
	- make a Person class and use it to draw many people.
	- make an Ironman and allow for him to shoot repulsor beam with his right hand
	*/
	class Person : public Game2D
	{
	public:
		float time = 0.0f;

		vec2 face = vec2(0.0f, 0.09f);
		vec2 eyes = vec2(0.05f, 0.11f);
		vec2 arms = vec2(0.0f, -0.1f);
		vec2 center_of_rot_arms = vec2(0.0f, 0.0f);
		vec2 legs = vec2(0.0f, -0.6f);
		vec2 body = vec2(0.0f, -0.1f);

			void draw()
			{
				// gold face
				beginTransformation();
				translate(face);
				drawFilledCircle(Colors::silver, 0.08f);
				endTransformation();

				// white eye
				beginTransformation();
				translate(eyes);
				drawFilledCircle(Colors::white, 0.01f); 
				endTransformation();

				// yellow arm; inside
				beginTransformation();
				translate(center_of_rot_arms);
				rotate(-sin(time*5.0f) * 30.0f);				// animation!
				scale(1.0f, 2.0f);
				translate(-center_of_rot_arms);
				translate(arms);
				drawFilledBox(Colors::silver, 0.05f, 0.18f);
				endTransformation();

				// green leg; inside
				beginTransformation();
				translate(legs);
				translate(0.0f, 0.2f);
				rotate(-sinf(time*5.0f + 3.141592f) * 30.0f);	// animation!
				translate(0.0f, -0.2f);
				drawFilledBox(Colors::silver, 0.1f, 0.4f);
				endTransformation();

				// red body
				beginTransformation();
				scale(1.0f, 2.0f);
				translate(body);
				drawFilledBox(Colors::silver, 0.13f, 0.2f);
				endTransformation();

				// yellow arm; outside
				beginTransformation();
				translate(center_of_rot_arms);
				rotate(sin(time*5.0f) * 30.0f);					// animation!
				scale(1.0f, 2.0f);
				translate(arms);
				translate(-center_of_rot_arms);
				drawFilledBox(Colors::silver, 0.05f, 0.18f);
				endTransformation();

				// green leg; outside
				beginTransformation();
				translate(legs);
				translate(0.0f, 0.2f);
				rotate(sinf(time*5.0f + 3.141592f) * 30.0f);	// animation!
				translate(0.0f, -0.2f);
				drawFilledBox(Colors::silver, 0.1f, 0.4f);
				endTransformation();

				time += this->getTimeStep();
			}
	};

	class Ironman : public Game2D
	{
	public:
		float time = 0.0f;

		vec2 face = vec2(0.0f, 0.09f);
		vec2 eyes = vec2(0.05f, 0.11f);
		vec2 arms = vec2(0.0f, -0.12f);
		vec2 center_of_rot_arms = vec2(0.0f, 0.0f);
		vec2 legs = vec2(0.0f, -0.6f);
		vec2 body = vec2(0.0f, -0.2f);
		vec2 flying_beam = vec2(0.0f, -0.8f);
		
		void draw()
		{
			// gold face
			beginTransformation();
			translate(face);
			drawFilledCircle(Colors::gold, 0.08f);
			endTransformation();

			// white eye
			beginTransformation();
			translate(eyes);
			drawFilledBox(Colors::skyblue, 0.03f, 0.01f);
			endTransformation();

			// yellow arm
			beginTransformation();
			translate(center_of_rot_arms);
			rotate(90.0f);				
			scale(1.0f, 2.0f);
			translate(arms);
			translate(-center_of_rot_arms);
			drawFilledBox(Colors::gold, 0.05f, 0.18f);
			endTransformation();

			// green leg
			beginTransformation();
			translate(legs);
			translate(0.0f, 0.2f);
			//rotate(-sinf(time*5.0f + 3.141592f) * 30.0f);	// animation!
			translate(0.0f, -0.2f);
			drawFilledBox(Colors::gold, 0.1f, 0.4f);
			endTransformation();

			// red body
			beginTransformation();
			translate(body);
			scale(1.0f, 2.0f);
			drawFilledBox(Colors::red, 0.13f, 0.2f);
			endTransformation();

			// flying beam
			beginTransformation();
			translate(flying_beam);
			drawFilledBox(Colors::skyblue, 0.1f, 0.05f);
			endTransformation();

			time += this->getTimeStep();
		}
	};

	class WalkingPerson : public Game2D
	{
	public:
		Person person1;
		Person person2;
		Ironman Mark3;

		const float offest = 0.5f;
		//person2.face.x += offest; // (*) Why do error occur?
		
	public:
		WalkingPerson()
			: Game2D("This is my digital canvas!", 1024, 768, false, 2)
		{
			person2.face.x += offest; // (*) Why is it fine here?
			person2.eyes.x += offest;
			person2.arms.x += offest;
			person2.center_of_rot_arms.x += offest;
			person2.legs.x += offest;
			person2.body.x += offest;
		}
		
		void update() override
		{
			// land
			beginTransformation();
			translate(0.0f, -3.3f);
			drawFilledBox(Colors::olive, 5.0f, 5.0f);
			endTransformation();

			person1.draw();
			person2.draw();

			if (isKeyPressed(GLFW_KEY_RIGHT))
			{
				Mark3.face.x += 0.5f * getTimeStep();
				Mark3.eyes.x += 0.5f * getTimeStep();
				Mark3.arms.x += 0.5f * getTimeStep();
				Mark3.center_of_rot_arms.x += 0.5f * getTimeStep();
				Mark3.legs.x += 0.5f * getTimeStep();
				Mark3.body.x += 0.5f * getTimeStep();
				Mark3.flying_beam.x += 0.5f * getTimeStep();
			}

			if (isKeyPressed(GLFW_KEY_LEFT))
			{
				Mark3.face.x -= 0.5f * getTimeStep();
				Mark3.eyes.x -= 0.5f * getTimeStep();
				Mark3.arms.x -= 0.5f * getTimeStep();
				Mark3.center_of_rot_arms.x -= 0.5f * getTimeStep();
				Mark3.legs.x -= 0.5f * getTimeStep();
				Mark3.body.x -= 0.5f * getTimeStep();
				Mark3.flying_beam.x -= 0.5f * getTimeStep();
			}

			if (isKeyPressed(GLFW_KEY_UP))
			{
				Mark3.face.y += 0.5f * getTimeStep();
				Mark3.eyes.y += 0.5f * getTimeStep();
				Mark3.arms.y += 0.5f * getTimeStep();
				Mark3.center_of_rot_arms.y += 0.5f * getTimeStep();
				Mark3.legs.y += 0.5f * getTimeStep();
				Mark3.body.y += 0.5f * getTimeStep();
				Mark3.flying_beam.y += 0.5f * getTimeStep();
			}

			if (isKeyPressed(GLFW_KEY_DOWN))
			{
				Mark3.face.y -= 0.5f * getTimeStep();
				Mark3.eyes.y -= 0.5f * getTimeStep();
				Mark3.arms.y -= 0.5f * getTimeStep();
				Mark3.center_of_rot_arms.y -= 0.5f * getTimeStep();
				Mark3.legs.y -= 0.5f * getTimeStep();
				Mark3.body.y -= 0.5f * getTimeStep();
				Mark3.flying_beam.y -= 0.5f * getTimeStep();
			}
			Mark3.draw();

			// repulsor beam
			if (isKeyPressed(GLFW_KEY_SPACE))
			{
				beginTransformation();
				translate(Mark3.arms.x + 3.0f, Mark3.arms.y + 0.115f);
				drawFilledBox(Colors::skyblue, 5.15f, 0.1f);
				endTransformation();
			}
			
			
		}
	};
}