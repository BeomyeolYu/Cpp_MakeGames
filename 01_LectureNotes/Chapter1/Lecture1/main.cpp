#include "Game2D.h"
#include "PrimitivesGallery.h"
#include "TankExample.h"
#include "FaceExample.h"
#include "WalkingPerson.h"
#include "SolarSystem.h"

namespace jm 
{
	class RotatingStarExample : public Game2D
	{
		float time = 0.0f;

		void update() override
		{
			rotate(time * 180.0f);
			drawFilledStar(Colors::gold, 0.4f, 0.25f);
			
			time += this->getTimeStep();
			std::cout << time << std::endl;
		}
	};

	class TransformationsExample : public Game2D
	{
		void update() override
		{
			/* const vec2 point = vec2(0.0f, 0.0f);
			= const vec2 point(0.0f, 0.0f); 동일한 형태를 생성자로 선언할 수도 있음. */
			const float dx = 0.1f;
			const float dy = 0.2f;
			const vec2 dxdy = vec2(0.0f, -0.3f);

			const vec2 p0 = vec2(0.0f + dx, 0.0f + dy);
			const vec2 p1(0.5f + dx, 0.5f + dy);
			const vec2 p2(0.5f + dx, 0.0f + dy);

			drawLine(Colors::red, p0, Colors::blue, p1);
			drawLine(Colors::red, p1, Colors::blue, p2);
			drawLine(Colors::red, p2, Colors::blue, p0);

			// 점을 하나하나 translate할 수 없으므로 좌표계 자체를 옮긴다.
			translate(dx, dy);

			// 누적하여 translate.
			drawLine(Colors::red, p0, Colors::blue, p1);
			drawLine(Colors::red, p1, Colors::blue, p2);
			drawLine(Colors::red, p2, Colors::blue, p0);

			// 누적하지 않는 방법.
			endTransformation();

			beginTransformation();

			translate(dxdy);

			drawLine(Colors::red, p0, Colors::blue, p1);
			drawLine(Colors::red, p1, Colors::blue, p2);
			drawLine(Colors::red, p2, Colors::blue, p0);
		}
	};

	class TransformationsBox : public Game2D
	{
		float time = 0;

		void update() override
		{
			setLineWidth(3.0f);

			drawWiredBox(Colors::red, 0.5f, 0.25f);
			
			// 컴퓨터 그래픽스에 사용되는 API는 내부적으로 역순으로 적용이 된다.
			beginTransformation();
			translate(0.25f, 0.0f);
			rotate(30.0f);
			drawWiredBox(Colors::blue, 0.5f, 0.25f);
			endTransformation();

			// rotate의 회전 기준은 원점이다.
			beginTransformation();
			translate(0.25f, 0.0f);
			drawWiredBox(Colors::green, 0.5f, 0.25f);
			endTransformation();

			beginTransformation();
			rotate(30.0f);
			translate(0.25f, 0.0f);
			drawWiredBox(Colors::green, 0.5f, 0.25f);
			endTransformation();

			// (1) 회전 중심을 바꾸는 방법.
			const vec2 center_of_rot = vec2(-0.25f, 0.0f);

			beginTransformation();
			translate(center_of_rot);	// 4th. 원위치.
			rotate(45.0f);				// 3rd. 원점을 중심으로 회전.
			translate(-center_of_rot);	// 2nd. 원점에 회전 중심이 오도록 통째로 이동.
			drawWiredBox(Colors::gold, 0.5f, 0.25f);
			drawPoint(Colors::black, center_of_rot, 5.0f); // 1st. 회전 중심을 결정한다.
			endTransformation();

			// (2) Scaling 예제; 변환들의 순서와 조합을 변경할 수 있다.
			rotate(time * 90.0f); // 자전과 공전을 동시에.
			translate(0.5f, 0.0f);
			rotate(time * 90.0f);
			scale(2.0f, 0.25f);   // 2배 & 1/4배
			drawWiredBox(Colors::olive, 0.5f, 0.5f);

			time += this->getTimeStep();
		}
	};

	class MouseExample : public Game2D
	{
	public:
		void update() override
		{
			const vec2 mouse_pos_wid = getCursorPos(false);
			std::cout << mouse_pos_wid << std::endl; // window coordinate는 y 부호가 반대이다.
		
			const vec2 mouse_pos_scr = getCursorPos(true); // screen coordinate로 변환
			std::cout << mouse_pos_scr << std::endl;
			
			if (isMouseButtonPressed(GLFW_MOUSE_BUTTON_RIGHT) == true)
			{
				translate(mouse_pos_scr);
				drawFilledCircle(Colors::red, 0.1f);
			}
			if (isMouseButtonPressed(GLFW_MOUSE_BUTTON_LEFT) == true)
			{
				translate(mouse_pos_scr);
				drawFilledCircle(Colors::gold, 0.1f);
			}
		}
	};
}

int main(void)
{
	/** Lecture 1.1 실시간 상호작용(Real-time Interactive) 어플리케이션의 구조 **/
	//jm::Game2D().init("This is my digital canvas!", 1280, 960, false).run();
	//jm::RotatingStarExample().run();
	//jm::RotatingStarExample().init("Rotating Star Example!", 1000, 1000, false, 2).run();
	
	/** Lecture 1.2 기본적인 그리기 - 이동, 회전, 애니메이션 **/
	//jm::TransformationsExample().run();
	//jm::TransformationsBox().run();
	//jm::PrimitivesGallery().init("Primitive Gallery", 1280, 960, false).run();
	//jm::SolarSystem().run();
	//jm::FaceExample().run();

	/** Lecture 1.3 상호작용 맛보기 - 키보드 입력과 반응(Response) **/
	//jm::TankExample().run();
	//jm::WalkingPerson().run();

	/** Lecture 1.4 마우스 입력 다루기 **/
	//jm::MouseExample().init("This is my digital canvas!", 1000, 1000, false).run();

	/** Lecture 1.5 사운드 파일 재생하기 - FMOD 라이브러리 **/
	// Lanuch the "fmod_test.sln"

	return 0;
}
