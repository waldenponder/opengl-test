#version 330 core

layout (location = 0) in vec3 aPosition;
layout (location = 1) in vec2 aCoor;
layout (location = 1) in vec3 aNormal;

uniform mat4 uModel;
uniform mat4 uView;
uniform mat4 uProjection;

out vec2 vTexCoor;
out vec3 vNormal;
out vec3 vPosition;

void main()
{
	gl_Position = uProjection * uView * uModel * vec4(aPosition.x, aPosition.y, aPosition.z, 1.0);
	vTexCoor = vec2(aCoor.x, aCoor.y);
	vNormal = (/*uView **/ uModel * vec4(aNormal, 1)).xyz;
	/*vNormal = normalize(vNormal);*/
	vPosition = (/*uView **/ uModel * vec4(aPosition, 1)).xyz;
}