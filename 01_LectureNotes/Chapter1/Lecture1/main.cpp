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
}

int main(void)
{
	/** Lecture 1.1 실시간 상호작용(Real-time Interactive) 어플리케이션의 구조 **/
	//jm::RotatingStarExample().run();
	jm::RotatingStarExample().init("Rotating Star Example!", 1000, 1000, false, 2).run();
	
	/** Lecture 1.2 기본적인 그리기 - 이동, 회전, 애니메이션 **/
	
	/** Lecture 1.1 Structure of Real-time Interactive Application **/
	//jm::MouseExample().init("This is my digital canvas!", 1000, 1000, false).run();
	//jm::Game2D().init("This is my digital canvas!", 1280, 960, false).run();
	//jm::PrimitivesGallery().init("Primitive Gallery", 1280, 960, false).run();
	//jm::SolarSystem().run();
	//jm::FaceExample().run();
	//jm::WalkingPerson().run();
	//jm::TankExample().run();

	return 0;
}
