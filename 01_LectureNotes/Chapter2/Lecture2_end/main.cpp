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
		RandomNumberGenerator rnd;

		Triangle my_tri[5];
		Circle my_cir[5];
		Box my_box[5];

		Example()
			: Game2D()
		{
			//random
			for (int i = 0; i < 5; ++i)
				my_tri[i].init({ rnd.getInt(0, 255), rnd.getInt(0, 255), rnd.getInt(0, 255) },
					vec2{ -1.0f + 0.5f * float(i), rnd.getFloat(-1.0f, 1.0f) },
					rnd.getFloat(0.1f, 0.3f));

			for (int i = 0; i < 5; ++i)
				my_cir[i].init({ rnd.getInt(0, 255), rnd.getInt(0, 255), rnd.getInt(0, 255) },
					vec2{ -1.0f + 0.5f * float(i), rnd.getFloat(-1.0f, 1.0f) },
					rnd.getFloat(0.1f, 0.3f));

			for (int i = 0; i < 5; ++i)
				my_box[i].init({ rnd.getInt(0, 255), rnd.getInt(0, 255), rnd.getInt(0, 255) },
					vec2{ -1.0f + 0.5f * float(i), rnd.getFloat(-1.0f, 1.0f) },
					rnd.getFloat(0.1f, 0.3f), rnd.getFloat(0.1f, 0.3f));
		}

		void update() override
		{
			for (int i = 0; i < 5; ++i)
				my_tri[i].draw();

			for (int i = 0; i < 5; ++i)
				my_cir[i].draw();

			for (int i = 0; i < 5; ++i)
				my_box[i].draw();
		}
	};
}

int main(void)
{
	jm::Example().run();
	//jm::Game2D().init("This is my digital canvas!", 1280, 960, false).run();
	//jm::PrimitivesGallery().run();

	return 0;
}
