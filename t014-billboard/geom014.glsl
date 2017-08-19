#version 330 core
layout(triangles) in;
layout(triangle_strip, max_vertices = 3) out;

uniform vec3  uViewPos;

in vec2 vTexCoor[];
in vec3 vNormal[];
in vec3 vPos[];

out vec2 gTexCoor;
out vec3 gNormal;
out vec3 gPos;
out vec3 gViewPos;

vec3 GetNormal()
{
	vec3 a = vec3(gl_in[0].gl_Position) - vec3(gl_in[1].gl_Position);
	vec3 b = vec3(gl_in[2].gl_Position) - vec3(gl_in[1].gl_Position);
	return normalize(cross(a, b));
}

void main()
{
	gl_PointSize = 5;
	
	vec3 n = GetNormal();
	gViewPos = uViewPos;
	gTexCoor = vTexCoor[0];
	gNormal = n;
	gPos = vPos[0];
	gl_Position = gl_in[0].gl_Position;
	EmitVertex();

	gTexCoor = vTexCoor[1];
	gNormal = n;
	gPos = vPos[1];
	gl_Position = gl_in[1].gl_Position;
	EmitVertex();

	gTexCoor = vTexCoor[2];
	gNormal = n;
	gPos = vPos[2];
	gl_Position = gl_in[2].gl_Position;
	EmitVertex();

	EndPrimitive();
}