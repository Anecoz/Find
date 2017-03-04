#include "Grid.h"
#include "OBJLoader.h"
#include "ShaderHandler.h"

#include <glm/glm.hpp>
#include <vector>
#include <iostream>

Grid::Grid()
	: _texture(nullptr)
	, _mesh(nullptr)
{
	std::vector<glm::vec3> verts;
	std::vector<unsigned> indices;
	std::vector<glm::vec3> normals;
	OBJLoader loader;
	if (!loader.loadFromFile("grid.model", verts, indices, normals)) {
		std::cerr << "Could not load grid file!" << std::endl;
		return;
	}

	_mesh = new VertexArrayObject(verts, indices, normals);
}

Grid::~Grid()
{
	delete _texture; 
	_texture = nullptr;
	delete _mesh;
	_mesh = nullptr;
}

void Grid::tick(Camera* cam, float deltaTime)
{
	float* data = _noiseGenerator.getHeightmapData(256, 256);

	if (_texture == nullptr) {
		_texture = new Texture(data, 256, 256);
	}
	else {
		_texture->updateData(data);
	}
}

void Grid::render(Camera* cam)
{
	ShaderHandler::_gridShader->comeHere();
	ShaderHandler::_gridShader->uploadTexture(0, HEIGHTMAP_NAME);
	glActiveTexture(GL_TEXTURE0);
	_texture->bind();
	ShaderHandler::_gridShader->uploadMatrix(cam->getProj(), PROJ_MTX_NAME);
	ShaderHandler::_gridShader->uploadMatrix(cam->getCameraMatrix(), CAM_MTX_NAME);
	ShaderHandler::_gridShader->uploadMatrix(glm::mat4(), MODEL_MTX_NAME);

	_mesh->draw();

	_texture->unbind();
	ShaderHandler::_gridShader->pissOff();
}
