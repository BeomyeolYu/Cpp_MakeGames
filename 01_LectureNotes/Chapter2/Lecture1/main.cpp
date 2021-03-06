#include "Game2D.h"
#include "Examples/PrimitivesGallery.h"
#include "RandomNumberGenerator.h"

/* Lecture 2.1 객체 지향은 편리해요 - 클래스와 캡슐화 */
// 방법(1): 단순 복사해서 붙여넣기.
namespace jm
{
	class Example1 : public Game2D
	{
	public:
		void update() override
		{
			// draw a house 1
			beginTransformation();
			{
				// wall
				drawFilledBox(Colors::yellow, 0.2f, 0.2f);

				// roof
				drawFilledTriangle(Colors::red, { -0.13f, 0.1f }, { 0.13f, 0.1f }, { 0.0f, 0.2f });
				drawWiredTriangle(Colors::red, { -0.13f, 0.1f }, { 0.13f, 0.1f }, { 0.0f, 0.2f });

				// window
				drawFilledBox(Colors::skyblue, 0.1f, 0.1f);
				drawWiredBox(Colors::gray, 0.1f, 0.1f);
				drawLine(Colors::gray, { 0.0f, -0.05f }, Colors::gray, { 0.0f, 0.05f });
				drawLine(Colors::gray, { -0.05f, 0.0f }, Colors::gray, { 0.05f, 0.0f });

			}
			endTransformation();

			// draw a house 2
			beginTransformation();
			{
				// difference
				translate(-0.5f, 0.0f);

				// wall
				drawFilledBox(Colors::yellow, 0.2f, 0.2f);

				// roof
				drawFilledTriangle(Colors::blue, { -0.13f, 0.1f }, { 0.13f, 0.1f }, { 0.0f, 0.2f });
				drawWiredTriangle(Colors::blue, { -0.13f, 0.1f }, { 0.13f, 0.1f }, { 0.0f, 0.2f });

				// window
				drawFilledBox(Colors::skyblue, 0.1f, 0.1f);
				drawWiredBox(Colors::gray, 0.1f, 0.1f);
				drawLine(Colors::gray, { 0.0f, -0.05f }, Colors::gray, { 0.0f, 0.05f });
				drawLine(Colors::gray, { -0.05f, 0.0f }, Colors::gray, { 0.05f, 0.0f });

			}
			endTransformation();
		}
	};
}

// 방법(2): 함수로 분리하고 매개변수(pos, ang)를 이용하기.
namespace jm
{
	void drawHouse(const RGB& roof_color, const vec2 pos, const float ang = 0.0f)
	{
		// draw a house
		beginTransformation();
		{
			translate(pos);
			rotate(ang);

			// wall
			drawFilledBox(Colors::yellow, 0.2f, 0.2f);

			// roof
			drawFilledTriangle(roof_color, { -0.13f, 0.1f }, { 0.13f, 0.1f }, { 0.0f, 0.2f });
			drawWiredTriangle(roof_color, { -0.13f, 0.1f }, { 0.13f, 0.1f }, { 0.0f, 0.2f });

			// window
			drawFilledBox(Colors::skyblue, 0.1f, 0.1f);
			drawWiredBox(Colors::gray, 0.1f, 0.1f);
			drawLine(Colors::gray, { 0.0f, -0.05f }, Colors::gray, { 0.0f, 0.05f });
			drawLine(Colors::gray, { -0.05f, 0.0f }, Colors::gray, { 0.05f, 0.0f });

		}
		endTransformation();
	}

	class Example2 : public Game2D
	{
	public:
		void update() override
		{
			drawHouse(Colors::red, { 0.0f, 0.0f }); // { , } = vec2( , )
			drawHouse(Colors::blue, { -0.5f, 0.0f });
			// -> 단, parameter가 많아질수록 함수가 복잡해진다.
		}
	};
}

/* 방법(3): class를 이용 -> 집을 그려준다는 기능에 집중하는 것이 아니라,
           House라는 존재(object)가 프로그램 안에 등장한다/생겨난다는 개념. 
		   -> draw()외에도 move(), rotate()등 더 많은 기능들이 구현 가능. 
		   -> 기능(member function) 뿐만 아니라 속성(member)도 가질 수 있다. */
namespace jm
{
	class House
	{
	private: // 교과서적인 코딩; private & setter $ getter
		// members
		RGB roof_color;
		RGB wall_color;
		vec2 pos;
		float ang = 0.0f; // 생성자로 초기화하는 것이 정석이지만 member 선언에서 바로 초기화 가능.

	public:
		House() // 생성자
			: roof_color(Colors::red), wall_color(Colors::yellow), pos(0.0f, 0.0f), ang(0.0f)
		{}

		// setter
		void setColor(const RGB& roof_input, const RGB& wall_input)
		{
			roof_color = roof_input;
			wall_color = wall_input;
		}
		void setPos(const vec2& pos_input)
		{
			pos = pos_input;
		}
		void setAng(const float& angle_input)
		{
			ang = angle_input;
		}

		// member function
		void draw()
		{
			// draw a house
			beginTransformation();
			{
				translate(pos);
				rotate(ang);

				// wall
				drawFilledBox(wall_color, 0.2f, 0.2f);

				// roof
				drawFilledTriangle(roof_color, { -0.13f, 0.1f }, { 0.13f, 0.1f }, { 0.0f, 0.2f });
				drawWiredTriangle(roof_color, { -0.13f, 0.1f }, { 0.13f, 0.1f }, { 0.0f, 0.2f });

				// window
				drawFilledBox(Colors::skyblue, 0.1f, 0.1f);
				drawWiredBox(Colors::gray, 0.1f, 0.1f);
				drawLine(Colors::gray, { 0.0f, -0.05f }, Colors::gray, { 0.0f, 0.05f });
				drawLine(Colors::gray, { -0.05f, 0.0f }, Colors::gray, { 0.05f, 0.0f });
			}
			endTransformation();
		}
	};
	
	class Example3 : public Game2D
	{
	public:
		/*
		House house1, house2;

		void update() override
		{
			house1.setPos({ 0.0f, 0.0f });  // wrong: house1.setPos(-0.5f, 0.0f);
			house2.setPos({ -0.5f, 0.0f }); // { , } = vec2{ , } 
			house2.setAng(10.0f);           // 왼쪽 방향이 +

			house1.draw();
			house2.draw();
		}
		*/
		House house1, house2;
		RandomNumberGenerator rnd;

		/* 
		[Question] 10개의 집을 만든다면?
		[Solution] Class의 특장점; (1) member를 array로 선언이 가능하다.
		                          (2) setter 및 member func.을 for 문으로 선언 가능. 
								     -> setter 사용 시의 장점. */
		House houses[10];

		Example3()
			: Game2D()
		{
			for (int i = 0; i < 10; ++i)
			{
				houses[i].setPos(vec2{ -1.3f + 0.3f * float(i), rnd.getFloat(-0.5f, 0.5f) });
				houses[i].setColor({ rnd.getInt(230, 255), rnd.getInt(0, 30), rnd.getInt(0, 30) },
					{ rnd.getInt(230, 255), rnd.getInt(230, 255), rnd.getInt(0, 30) });
				houses[i].setAng(rnd.getFloat(0.0f, 360.f));
			}
		}

		void update() override
		{
			for (int i = 0; i < 10; ++i)
			{
				houses[i].draw();
			}
		}
	};
}

int main(void)
{
	// ※ Debug에서는 오류가 발생하고 Release에서는 실행된다.

	//jm::Example1().run();
	//jm::Example2().run();
	jm::Example3().run();

	//jm::Game2D().init("This is my digital canvas!", 1280, 960, false).run();
	//jm::PrimitivesGallery().run();
	
	return 0;
}
