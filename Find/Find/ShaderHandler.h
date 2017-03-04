#pragma once

#include "Shader.h"

class ShaderHandler {
public:
	static Shader* _gridShader;

	static void init();
	static void cleanUp();
};
