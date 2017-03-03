#version 430

layout (location = 0) in vec3 inPosition;
layout (location = 1) in vec3 inNormal;

uniform mat4 projMatrix;
uniform mat4 camMatrix;
uniform float scale;

out vec3 outNormal;
out vec3 outPos;

#define MOD2 vec2(3.07965, 7.1235)
const mat2 rotate2D = mat2(1.3623, 1.7531, -1.7131, 1.4623);
vec2 add = vec2(1.0, 0.0);

float Hash12(vec2 p)
{
	p  = fract(p / MOD2);
    p += dot(p.xy, p.yx+19.19);
    return fract(p.x * p.y);
}

float Noise( in vec2 x )
{
    vec2 p = floor(x);
    vec2 f = fract(x);
    f = f*f*(3.0-2.0*f);
    float n = p.x + p.y*57.0;
    
    float res = mix(mix( Hash12(p),          Hash12(p + add.xy),f.x),
                    mix( Hash12(p + add.yx), Hash12(p + add.xx),f.x),f.y);
    return res;
}

float calcNeutral(vec2 pos)
{
	pos = pos*0.025;
	float w = (Noise(pos*.25)*0.75+.15);
	w = 66.0 * w * w;
	float f = .0;
	for (int i = 0; i < 5; i++)
	{
		f += w * Noise(pos);
		w =  - w * 0.4;	//...Flip negative and positive for varition	   
		pos = rotate2D * pos;
	}
	float ff = Noise(pos*.002);
	f += pow(abs(ff), 5.0)*275.-25.0;
	
	// That's the last of the low resolution, now go down further for the Normal data...
	for (int i = 0; i < 6; i++)
	{
		f += w * Noise(pos);
		w =  - w * 0.4;
		pos = rotate2D * pos;
	}	
	
	return f;
}

void main() {
	// Offset the height using noise function first
	vec3 scaledPos = inPosition * scale;
	float height = calcNeutral(scaledPos.xz);
	
	// Now offset using the normal
	vec3 vertPos = scaledPos + (inNormal * height);

	outNormal = inNormal;
	outPos = vertPos;

	gl_Position = projMatrix * camMatrix * vec4(vertPos, 1.0);
}