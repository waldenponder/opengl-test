#version 330 core

out vec4 fColor;
in vec3 vTexCoor;

uniform samplerCube cubemap;

void main()
{	
	fColor = texture(cubemap, vTexCoor);
}