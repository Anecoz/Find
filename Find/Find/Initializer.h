#pragma once
#include <GL\glew.h>
#include <GLFW\glfw3.h>
#include <string>
#include <glm\glm.hpp>

class Initializer {
public:
	Initializer();
	~Initializer() = default;

	GLFWwindow* init();

private:
	// Settings
	bool _shouldUseMSAA = false;
	int _MSAASamples = 4;

	bool _useVSync = true;

	int _screenWidth = 1280;
	int _screenHeight = 720;

	std::string _windowTitle = "Planet";

	glm::vec4 _clearColor{ 0.2, 0.2, 0.5, 1.0 };
};