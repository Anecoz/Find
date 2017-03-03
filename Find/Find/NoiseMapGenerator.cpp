#include "NoiseMapGenerator.h"
#include "libnoise/noise.h"
#include <iostream>

using namespace noise;

NoiseMapGenerator::NoiseMapGenerator()
{
	module::Perlin perlinModule;
	double value = perlinModule.GetValue(14.50, 20.25, 75.75);
	std::cout << "Value: " << value << std::endl;
}

NoiseMapGenerator::~NoiseMapGenerator()
{
}
