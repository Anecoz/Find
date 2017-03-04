#version 430

layout ( triangles ) in;
layout (triangle_strip, max_vertices = 3) out;

in vec3 v_vertex[];

out vec3 fragNormal;

void main() {
	vec3 normal = normalize( cross(v_vertex[2]-v_vertex[0], v_vertex[1]-v_vertex[0] ) );

	for (int i = 0; i < 3; i++) {
		fragNormal = normal;
		gl_Position = gl_in[i].gl_Position;
		EmitVertex();
	}
	
	EndPrimitive();
}