#include "Game2D.h"
#include "Examples/PrimitivesGallery.h"
#include "RandomNumberGenerator.h"
#include "Triangle.h"
#include "Circle.h"
#include "Box.h"

namespace jm
{
	class Example : public Game2D
	{
	public:
		Triangle my_tri;
		Circle my_cir;
		Box my_box;

		Example()
			: Game2D()
		{
			my_tri.init(Colors::gold, vec2{ -0.5f, 0.2f }, 0.25f);
			my_cir.init(Colors::olive, vec2{ 0.1f, 0.1f }, 0.2f);
			my_box.init(Colors::blue, vec2{ 0.0f, 0.5f }, 0.15f, 0.25f);
		}

		void update() override
		{
			/* 
			my_tri.draw();
			my_cir.draw();
			my_box.draw(); 에서
			draw();는 부모 class에 속해있으므로, 부모 class의 포인터를 사용해서 호출할 수 있다.
			*/


		}
	};
}

int main(void)
{
	/* Lecture 2.3 다형성으로 유연하게 
	 - 상속에 다형성을 추가하게되면 기존의 코드를 유지보수하거나 새로운 코드를 추가할 때 훨씬 더 편하다.
	*/

	jm::Example().run();
	//jm::Game2D().init("This is my digital canvas!", 1280, 960, false).run();
	//jm::PrimitivesGallery().run();

	return 0;
}
