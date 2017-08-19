#version 330 core
layout (location = 0) in vec3 position;
layout (location = 1) in vec3 col;
layout (location = 2) in vec2 coor;

out vec3 vert_color;
out vec2 texCoor;

void main()
{
	gl_Position = vec4(position.x, position.y, position.z, 1.0);
	vert_color = col;
	texCoor = vec2(coor.x, coor.y);
}