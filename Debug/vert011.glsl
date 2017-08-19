#version 330 core
layout (location = 0) in vec3 aPosition;
layout (location = 1) in vec2 aCoor;
layout (location = 2) in vec3 aNormal;
layout(location = 3) in vec3 offset;

uniform mat4 uModel;
uniform mat4 uView;
uniform mat4 uProjection;
uniform float uTexCoordScale;

out vec2 vTexCoor;
out vec3 vNormal;
out vec3 vPos;

//float rand(vec2 co)
//{
//	return fract(sin(dot(co.xy, vec2(12.9898, 78.233))) * 43758.5453);
//}

void main()
{
	vec3 temp = aPosition;
	if (gl_InstanceID > 0)
		temp = temp + offset;

	gl_Position = uProjection * uView * uModel * vec4(aPosition + offset, 1.0);
	vTexCoor = aCoor * uTexCoordScale;
	vNormal = mat3(transpose(inverse(uModel))) * aNormal;
	vPos = (uModel * vec4(aPosition, 1.0f)).xyz;
}