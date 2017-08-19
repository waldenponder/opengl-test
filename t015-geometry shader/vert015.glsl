#version 330 core
layout (location = 0) in vec2 aPosition;
layout(location = 1) in vec3 aColor;

out Varing
{
	vec3 color;
} var;
 
void main()
{
	gl_PointSize = 5;
	gl_Position = vec4(aPosition, 0, 1);

	var.color = aColor;
}