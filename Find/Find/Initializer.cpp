#include "Initializer.h"
#include "KeyInput.h"
#include "MousePosInput.h"
#include "MouseButtonInput.h"
#include <iostream>

static void errorCallback(int error, const char* description) {
	std::cerr << description << std::endl;
}

Initializer::Initializer() {

}

GLFWwindow* Initializer::init() {
	GLFWwindow* window;
	glfwSetErrorCallback(errorCallback);
	if (!glfwInit())
		exit(-1);

	if (_shouldUseMSAA)
		glfwWindowHint(GLFW_SAMPLES, _MSAASamples);
	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

	window = glfwCreateWindow(_screenWidth, _screenHeight, _windowTitle.c_str(), NULL, NULL);

	if (!window) {
		std::cerr << "Failed to open GLFW window" << std::endl;
		glfwTerminate();
		exit(-2);
	}

	glfwMakeContextCurrent(window);
	int vsync = _useVSync ? 1 : 0;
	glfwSwapInterval(vsync);

	// Set input callbacks
	glfwSetKeyCallback(window, KeyInput::invoke);
	glfwSetCursorPosCallback(window, MousePosInput::invoke);
	glfwSetMouseButtonCallback(window, MouseButtonInput::invoke);

	// Check for errors
	GLenum err = glewInit();
	if (err != GLEW_OK) {
		std::cerr << "Error: " << glewGetErrorString(err) << std::endl;
		exit(-3);
	}

	glClearColor(_clearColor.r, _clearColor.g, _clearColor.b, _clearColor.a);
	glEnable(GL_DEPTH_TEST);
	std::cout << "Vendor: " << glGetString(GL_VENDOR) << std::endl;
	std::cout << "Renderer: " << glGetString(GL_RENDERER) << std::endl;
	std::cout << "Supported OpenGL version: " << glGetString(GL_VERSION) << std::endl;

	return window;
}