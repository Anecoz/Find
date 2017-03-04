#version 430

layout (location = 0) out vec4 outColor;

in vec3 fragNormal;

void main() {
	outColor = vec4(fragNormal.x, fragNormal.y, fragNormal.z, 1.0);
}