#include "NoiseMapGenerator.h"

#include <iostream>

using namespace noise;

NoiseMapGenerator::NoiseMapGenerator()
{
	_heightMapBuilder.SetSourceModule(_perlinModule);
	_heightMapBuilder.SetDestNoiseMap(_heightMap);
}

NoiseMapGenerator::~NoiseMapGenerator()
{
}

float* NoiseMapGenerator::getHeightmapData(int width, int height)
{
	_heightMapBuilder.SetDestSize(width, height);
	_heightMapBuilder.SetBounds(2.0, 6.0, 1.0, 5.0);
	_heightMapBuilder.Build();

	return _heightMap.GetSlabPtr();
}
