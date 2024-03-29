#version 330 core
layout(location = 0) in vec3 position;
layout(location = 1) in vec2 coor;

uniform mat4 vert_mat;
out vec2 texCoor;
out vec2 MCposition;

void main()
{
	gl_Position = vert_mat * vec4(position.x, position.y, position.z, 1.0);
	texCoor = coor;

	//MCposition = gl_Position.xy;
	MCposition = texCoor;
}