#version 330 core
layout (location = 0) in vec3 position;
layout (location = 1) in vec3 col;
layout (location = 2) in vec2 coor;

uniform mat4 uModel;
uniform mat4 uView;
uniform mat4 uProjection;

out vec3 vert_color;
out vec2 texCoor;

void main()
{
	gl_Position = uProjection * uView * uModel * vec4(position, 1.0);
	vert_color = col;
	texCoor = coor;
}