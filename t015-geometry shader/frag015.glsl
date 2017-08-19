#version 330 core

out vec4  color;

in Varing
{
	vec3 color;
} var;

void main()
{
	color = vec4(var.color, 1.0f);
}