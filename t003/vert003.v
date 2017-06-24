#version 330 core
layout(location=0) in vec3 pos;
layout(location=1) in vec2 coor;

uniform mat4 vert_mat;
out vec2 Coor;

void main()
{
   gl_Position = vert_mat * vec4(pos, 1);
   //gl_Position = vec4(pos, 1);
   Coor = vec2(coor.x, 1 - coor.y);
}