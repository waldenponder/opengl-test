#version 330 core
layout(triangles) in;
layout(triangle_strip, max_vertices = 6) out;

uniform vec3  uViewPos;

in vec2 vTexCoor[];
in vec3 vNormal[];
in vec3 vPos[];

out vec2 gTexCoor;
out vec3 gNormal;
out vec3 gPos;
out vec3 gViewPos;
out vec3 gTestColor;

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
	
	vec3 front = uViewPos - gl_in[0].gl_Position.xyz;
	vec3 right = cross(front, vec3(0, 1, 0));
	vec3 up = cross(front, right);
	
	vec3 pos1, pos2, pos3, pos4;
	pos1 = gl_in[0].gl_Position.xyz;
	pos2 = pos1 + up * .2;
	pos3 = pos2 + right * .2;
	//pos4 = pos3 + up * 2;

	vec3 testColor = right;
	   
	vec4 v1 = gl_in[0].gl_Position;
	vec4 v2 = gl_in[1].gl_Position;
	vec4 v3 = gl_in[2].gl_Position;

	gTestColor = testColor;

	//1
	gTexCoor = vTexCoor[0];
	gNormal = n;
	gPos = vPos[0];
	gl_Position = v1;// vec4(pos1, 1);
	EmitVertex();

	gTexCoor = vTexCoor[1];
	gNormal = n;
	gPos = vPos[1];
	gl_Position = v2;// vec4(pos2, 1);
	EmitVertex();

	gTexCoor = vTexCoor[2];
	gNormal = n;
	gPos = vPos[2];
	gl_Position = v3;// vec4(pos3, 1);
	EmitVertex();
}