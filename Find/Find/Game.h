#pragma once
#include <GL\glew.h>
#include <GLFW\glfw3.h>
#include "EntityHandler.h"
#include "Camera.h"
#include "Initializer.h"

class Game {
public:
	Game();
	~Game();

	void run();

private:
	GLFWwindow* _window;
	EntityHandler* _entityHandler;
	Camera* _camera;
	Initializer* _initializer;

	void tick();
	void render();
};