#version 430

layout (location = 0) in vec3 inPosition;
layout (location = 1) in vec3 inNormal;

out vec3 worldCoords;

uniform mat4 projMatrix;
uniform mat4 camMatrix;
uniform mat4 modelMatrix;
uniform sampler2D heightmap;

float linearMapping(float value, float srcMin, float srcMax, float dstMin, float dstMax) {
	return (value - srcMin) * (dstMax - dstMin) / (srcMax - srcMin) + dstMin;
}

void main() {	
	float normX = linearMapping(inPosition.x, -128.0, 128.0, 0.0, 1.0);
	float normZ = linearMapping(inPosition.z, -128.0, 128.0, 0.0, 1.0);
	float val = texture(heightmap, vec2(normX, normZ)).r;
	vec3 heightened = vec3(inPosition.x, val * 50.0, inPosition.z);
	worldCoords = vec4(modelMatrix * vec4(heightened, 1.0)).xyz;
	gl_Position = projMatrix * camMatrix * modelMatrix * vec4(heightened, 1.0);
}