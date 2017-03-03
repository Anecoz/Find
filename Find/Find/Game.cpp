#include "Game.h"
#include "Camera.h"
#include "Initializer.h"
#include "ShaderHandler.h"
#include "KeyInput.h"
#include "MouseButtonInput.h"
#include "MousePosInput.h"
#include <iostream>

static void errorCallback(int error, const char* description) {
	std::cerr << description << std::endl;
}

Game::Game() {
	_initializer = new Initializer();
	_window = _initializer->init();
	ShaderHandler::init();

	if (!_window) {
		std::cerr << "Something went wrong." << std::endl;
	}

	_entityHandler = new EntityHandler();
	_camera = new Camera();
	_oldTime = glfwGetTime();
}

Game::~Game() {
	ShaderHandler::cleanUp();
}

void Game::run() {
	while (!glfwWindowShouldClose(_window)) {
		tick();
		render();		
		if (KeyInput::isKeyClicked(GLFW_KEY_ESCAPE))
			break;
	}

	return;
}

void Game::tick() {
	glfwPollEvents();

	double now = glfwGetTime();
	double deltaTime = now - _oldTime;
	_oldTime = now;

	_camera->update(deltaTime);
	glfwSetCursorPos(_window, Camera::MOUSE_WARP_X, Camera::MOUSE_WARP_Y);
	
	_entityHandler->tick(_camera, deltaTime);
}

void Game::render() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	_entityHandler->render(_camera);

	glfwSwapBuffers(_window);
}