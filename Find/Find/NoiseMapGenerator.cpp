#include "NoiseMapGenerator.h"

#include <iostream>

using namespace noise;

NoiseMapGenerator::NoiseMapGenerator()
{
	_perlinModule.SetFrequency(0.03);
	_perlinModule.SetLacunarity(1.5);
	_perlinModule.SetOctaveCount(6);
	_heightMapBuilder.SetSourceModule(_perlinModule);
	_heightMapBuilder.SetDestNoiseMap(_heightMap);
}

NoiseMapGenerator::~NoiseMapGenerator()
{
}

float* NoiseMapGenerator::getHeightmapData(glm::vec2& pos, int width, int height)
{
	_heightMapBuilder.SetDestSize(width, height);
	_heightMapBuilder.SetBounds(pos.x, pos.x + (float)width, pos.y, pos.y + (float)height);
	_heightMapBuilder.Build();

	return _heightMap.GetSlabPtr();
}
