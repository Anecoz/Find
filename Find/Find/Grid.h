#pragma once
#include "Texture.h"
#include "NoiseMapGenerator.h"
#include "VertexArrayObject.h"
#include "Camera.h"
#include <string>

class Grid
{
public:
	Grid();
	~Grid();

	void tick(Camera* cam, float deltaTime);
	void render(Camera* cam);

private:
	Texture* _texture;
	VertexArrayObject* _mesh;
	NoiseMapGenerator _noiseGenerator;

	std::string HEIGHTMAP_NAME = "heightmap";
	std::string MODEL_MTX_NAME = "modelMatrix";
	std::string CAM_MTX_NAME = "camMatrix";
	std::string PROJ_MTX_NAME = "projMatrix";

	const int SIZE = 256;

	glm::vec2 _position;
};

