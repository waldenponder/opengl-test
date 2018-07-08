#version 330 core

uniform mat4 u_projectionMatrix;
uniform mat4 u_modelViewMatrix;

layout (location = 0)in vec4 a_vertex;
//layout (location = 1)in vec3 a_normal;

out vec3 v_ray;

void main(void)
{
	v_ray = normalize(a_vertex.xyz);
	
	gl_Position = u_projectionMatrix*u_modelViewMatrix*a_vertex;
}
