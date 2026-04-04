#pragma once
#include "external/GLFW/glfw3.h"

namespace ve {
	/// <summary>
	/// A class for handling the window context of the game engine. 
	/// Handles window creation, termination, and updates.
	/// </summary>

	class Window {

	private:

		GLFWwindow* window = NULL;

		int height = 1080;
		int width = 1920;

	public:
		void init();
		bool isOpen();
		void update();
		void terminate();
		GLFWwindow* getWindow();

		float getAspectRatio();
	};
}
