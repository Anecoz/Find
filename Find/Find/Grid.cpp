#include "Grid.h"
#include "OBJLoader.h"
#include "ShaderHandler.h"

#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>
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
	glm::vec2 pos;
	pos.x = floor(cam->getPos().x);
	pos.y = floor(cam->getPos().z);
	float* data = _noiseGenerator.getHeightmapData(pos, SIZE, SIZE);

	if (_texture == nullptr) {
		_texture = new Texture(data, SIZE, SIZE);
	}
	else {
		_texture->updateData(data);
	}
	_position = pos;
}

void Grid::render(Camera* cam)
{
	ShaderHandler::_gridShader->comeHere();
	ShaderHandler::_gridShader->uploadTexture(0, HEIGHTMAP_NAME);
	glActiveTexture(GL_TEXTURE0);
	_texture->bind();

	ShaderHandler::_gridShader->uploadMatrix(cam->getProj(), PROJ_MTX_NAME);
	ShaderHandler::_gridShader->uploadMatrix(cam->getCameraMatrix(), CAM_MTX_NAME);
	ShaderHandler::_gridShader->uploadMatrix(glm::translate(glm::vec3(_position.x, 0, _position.y)), MODEL_MTX_NAME);

	_mesh->draw();

	_texture->unbind();
	ShaderHandler::_gridShader->pissOff();
}
