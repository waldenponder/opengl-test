#version 330 core
layout (location = 0) in vec3 aPosition;

uniform mat4 uView;
uniform mat4 uProjection;

out vec3 vTexCoor;

void main()
{
	gl_Position = uProjection * uView  * vec4(aPosition.x, aPosition.y, aPosition.z, 1.0);
	vTexCoor = vec3(aPosition.x, aPosition.y, aPosition.z);
}