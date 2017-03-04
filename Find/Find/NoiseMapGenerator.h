#pragma once
#include "libnoise/noise.h"
#include "noiseutils.h"

class NoiseMapGenerator
{
public:
	NoiseMapGenerator();
	~NoiseMapGenerator();

	float* getHeightmapData(int width, int height);

private:
	module::Perlin _perlinModule;
	utils::NoiseMap _heightMap;
	utils::NoiseMapBuilderPlane _heightMapBuilder;
};

