#version 330 core
layout (location = 0) in vec3 aPosition;
layout (location = 1) in vec2 aCoor;
layout (location = 1) in vec3 aNormal;

uniform mat4 uModel;
uniform mat4 uView;
uniform mat4 uProjection;
uniform float uTexCoordScale;

out vec2 vTexCoor;
out vec3 vNormal;
out vec3 vPos;

void main()
{
	gl_Position = uProjection * uView * uModel * vec4(aPosition.x, aPosition.y, aPosition.z, 1.0);
	vTexCoor = aCoor * uTexCoordScale;
	vNormal = mat3(transpose(inverse(uModel))) * aNormal;
	vPos = (uModel * vec4(aPosition, 1.0f)).xyz;
}