#include <iostream>
#include <GL\glew.h>
#include <GLFW\glfw3.h>

static void errorCallback(int error, const char* description)
{
	std::cerr << description << std::endl;
}

int main()
{
	GLFWwindow* window;
	glfwSetErrorCallback(errorCallback);

	if (!glfwInit()) {
		exit(-1);
	}

	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

	window = glfwCreateWindow(800, 600, "Find - A dank game", NULL, NULL);

	if (!window) {
		std::cerr << "Failed to open GLFW window!" << std::endl;
		glfwTerminate();
		exit(-2);
	}

	glfwMakeContextCurrent(window);
	glfwSwapInterval(1);

	GLenum err = glewInit();
	if (err != GLEW_OK) {
		std::cerr << "Error: " << glewGetErrorString(err) << std::endl;
		exit(-3);
	}

	glClearColor(0.2, 0.2, 0.5, 1.0);
	glEnable(GL_DEPTH_TEST);

	std::cout << "Vendor: " << glGetString(GL_VENDOR) << std::endl;
	std::cout << "Renderer: " << glGetString(GL_RENDERER) << std::endl;
	std::cout << "Supported OpenGL version: " << glGetString(GL_VERSION) << std::endl;
	
    return 0;
}