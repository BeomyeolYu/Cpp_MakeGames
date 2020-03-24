#pragma once

#include "RGB.h"
#include "Vector2.h"
#include "Vector3.h"
#include "Colors.h"
#include "Timer.h"
#include "DrawFunctions.h"

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <thread>         // std::this_thread::sleep_for
#include <iostream>
#include <vector>
#include <string>
#include <map>

namespace jm
{
	using vec2 = Vector2<float>;
	using vec3 = Vector3<float>;

	class Game2D
	{
	private:
		int width = 640;
		int height = 480;

		GLFWwindow* glfw_window = nullptr;

		Timer timer;

		float spf = 1.0f / 60.0f;		 // second(s) per frame; fps의 역수

		// control options
		std::map<int, bool> key_status;  // key_id, is_pressed
		std::map<int, bool> mbtn_status; // mouse_button_id, is_pressed
		bool draw_grid = true;           // draw grid or not

	public:
		Game2D()
		{}

		// Setting; full screen mode, the number of display
		Game2D(const std::string& _title, const int& _width, const int& _height,
			const bool & use_full_screen = false, const int & display_ix = 0);
		
		~Game2D();

		Game2D & init(const std::string& _title, const int& _width, const int& _height,
			const bool & use_full_screen = false, const int & display_ix = 0);

		// Error reporting function
		void reportErrorAndExit(const std::string& function_name, const std::string& message);

		bool isKeyPressed(const int& key);
		bool isKeyReleased(const int & key);
		bool isKeyPressedAndReleased(const int& key);

		bool isMouseButtonPressed(const int& mbtn);
		bool isMouseButtonReleased(const int& mbtn);
		bool isMouseButtonPressedAndReleased(const int& mbtn);

		vec2 getCursorPos(const bool& screen_coordinates = true);

		float getTimeStep(); // 한 프레임 당 시간이 얼마나 걸리는지 측정해 주는 func.

		void drawGrid();

		void run(); // 의 while이 main loop

		virtual void update() // void run();내의 update();가 실행될 때 override됨 
		{                     // 하나의 virtual func.만 사용하여 구조를 파악한다
			// draw
			// play sould
			// physics update
			// etc.
		}
	};
}