#pragma once
#include "libnoise/noise.h"
#include "noiseutils.h"
#include <glm/glm.hpp>

class NoiseMapGenerator
{
public:
	NoiseMapGenerator();
	~NoiseMapGenerator();

	float* getHeightmapData(glm::vec2& pos, int width, int height);

private:
	module::Perlin _perlinModule;
	utils::NoiseMap _heightMap;
	utils::NoiseMapBuilderPlane _heightMapBuilder;
};

