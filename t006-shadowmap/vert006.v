#version 330 core

layout (location = 0) in vec3 aPosition;
layout (location = 1) in vec2 aCoor;
layout (location = 1) in vec3 aNormal;

uniform mat4 uModel;
uniform mat4 uView;
uniform mat4 uProjection;
uniform mat4 uLightSpace;

out vec2 vTexCoor;
out vec3 vNormal;
out vec3 vPosition;
out vec4 vPosInLightSpace;

void main()
{
	gl_Position = uProjection * uView * uModel * vec4(aPosition, 1.0);
	vTexCoor = aCoor;
	vNormal = (uModel * vec4(aNormal, 1)).xyz;
	vPosition = (uModel * vec4(aPosition, 1)).xyz;
	vPosInLightSpace = uLightSpace * vec4(vPosition, 1);
	//vPosInLightSpace = uLightSpace * uModel * vec4(aPosition, 1);
}