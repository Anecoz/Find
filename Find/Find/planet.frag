#version 430

layout (location = 0) out vec4 outColor;

in vec3 outNormal;
in vec3 outPos;

uniform vec3 cameraPos;

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

vec3 calcNeutralCol(vec3 pos, vec3 normal, float dis)
{
	vec3 mat;
	vec3 dir = normalize(pos-cameraPos);
	
	vec3 matPos = pos;// * 2.0;// ... I had change scale halfway though, this lazy multiply allow me to keep the graphic scales I had

	float disSqrd = dis * dis;// Squaring it gives better distance scales.

	float f = clamp(Noise(matPos.xz*.05), 0.0,1.0);//*10.8;
	f += Noise(matPos.xz*.1+normal.yz*1.08)*.85;
	f *= .55;
	vec3 m = mix(vec3(.63*f+.2, .7*f+.1, .7*f+.1), vec3(f*.43+.1, f*.3+.2, f*.35+.1), f*.65);
	mat = m*vec3(f*m.x+.36, f*m.y+.30, f*m.z+.28);
	// Should have used smoothstep to add colours, but left it using 'if' for sanity...
	/*if (normal.y < .5)
	{
		float v = normal.y;
		float c = (.5-normal.y) * 4.0;
		c = clamp(c*c, 0.1, 1.0);
		f = Noise(vec2(matPos.x*.09, matPos.z*.095+matPos.yy*0.15));
		f += Noise(vec2(matPos.x*2.233, matPos.z*2.23))*0.5;
		mat = mix(mat, vec3(.4*f), c);
	}*/

	// Grass. Use the normal to decide when to plonk grass down...
	if (matPos.y < 45.35 && normal.y > .65)
	{

		m = vec3(Noise(matPos.xz*.023)*.5+.15, Noise(matPos.xz*.03)*.6+.25, 0.0);
		m *= (normal.y- 0.65)*.6;
		mat = mix(mat, m, clamp((normal.y-.65)*1.3 * (45.35-matPos.y)*0.1, 0.0, 1.0));
	}
	// Beach effect...
	if (matPos.y < 1.45)
	{
		if (normal.y > .4)
		{
			f = Noise(matPos.xz * .084)*1.5;
			f = clamp((1.45-f-matPos.y) * 1.34, 0.0, .67);
			float t = (normal.y-.4);
			t = (t*t);
			mat = mix(mat, vec3(.09+t, .07+t, .03+t), f);
		}
		// Cheap under water darkening...it's wet after all...
		if (matPos.y < 0.0)
		{
			mat *= .5;
		}
	}

	return (1.0 - exp(-mat * 3.0)) * 1.0024;;
}

void main() {
	outColor = vec4(calcNeutralCol(outPos, outNormal, 2), 1.0);
}