#include "Game2D.h"
#include "Examples/PrimitivesGallery.h"
#include "RandomNumberGenerator.h"
#include "Triangle.h"
#include "Circle.h"
#include "Square.h"
#include "Pentagon.h"

namespace jm
{
	class Example : public Game2D
	{
	public:
		// (1) 상속을 이용하지 않고 각 도형의 class를 만드는 경우.
		Triangle my_tri;
		Circle my_cir;

		// (2) 상속을 이용 
		/* Square와 Pentagon의 중복되는 부분(void draw(), pos, color, size)을 모은 뒤에,
		   부모 class( = GeometricObject)를 생성/
		*/
		Square my_squ;
		Pentagon my_pent;

		Example()
			: Game2D()
		{
			// (1)
			my_tri.pos = vec2{ -0.5f, -0.05f };
			my_tri.color = Colors::yellow;
			my_tri.size = 0.3f;

			my_cir.pos = vec2{ 0.0f, 0.0f };
			my_cir.color = Colors::yellow;
			my_cir.size = 0.15f;

			// (2)
			my_squ.init(vec2{ 0.5f, 0.3f }, Colors::red, 0.3f);
			my_pent.init(vec2{ 0.5f, -0.3f }, Colors::red, 0.2f);
		}

		void update() override
		{
			// (1)
			my_tri.draw();
			my_cir.draw();

			// (2)
			my_squ.draw();
			my_pent.draw();

			//// blue box
			//beginTransformation();
			//{
			//	translate(vec2{ 0.5f, 0.0f });
			//	drawFilledBox(Colors::blue, 0.25f, 0.3f);
			//}
			//endTransformation();
		}
	};
}

int main(void)
{
	/* Lecture 2.2.1 상속으로 깔끔하게 [1/2]
	- 상속의 의미
	 [1] 개체(object) 간의 관계를 구조적으로 정리해가는 것.
	 [2] 공통되는 요소를 한 군데 모아놓고 여러 object들이 함께 사용하는 것.
	 [3] 특정 기능을 코딩을 할 때마다 반복적으로 구현할 필요 없이 재사용하는 것.

	 -> 상속을 이용하여 우리가 작성하는 코드들을
	  (1) 확장하기 편리하고
	  (2) 간단하면서도 깨끗하고
	  (3) 짜임새 있게 만들어가는 방법을 학습.
	*/

	jm::Example().run();
	//jm::Game2D().init("This is my digital canvas!", 1280, 960, false).run();
	//jm::PrimitivesGallery().run();

	return 0;
}
