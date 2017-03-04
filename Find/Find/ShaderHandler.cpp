#include "ShaderHandler.h"
#include <GL\glew.h>
#include <string>

Shader* ShaderHandler::_gridShader;

void ShaderHandler::init()
{
	_gridShader = new Shader("grid.vert", "grid.geom", "grid.frag");
}

void ShaderHandler::cleanUp()
{
	delete _gridShader;
	_gridShader = nullptr;
}