#version 430

layout (location = 0) out vec4 outColor;

in vec3 worldCoords;

uniform sampler2D heightmap;

float linearMapping(float value, float srcMin, float srcMax, float dstMin, float dstMax) {
	return (value - srcMin) * (dstMax - dstMin) / (srcMax - srcMin) + dstMin;
}

void main() {
	float worldX = linearMapping(worldCoords.x, -128.0, 128.0, 0.0, 1.0);
	float worldZ = linearMapping(worldCoords.z, -128.0, 128.0, 0.0, 1.0);
	float val = texture(heightmap, vec2(worldX, worldZ)).r;
	outColor = vec4(val, val, val, 1.0);
}