#pragma once
#include "external/GLFW/glfw3.h"

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
