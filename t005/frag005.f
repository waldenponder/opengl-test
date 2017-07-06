#version 330 core

uniform sampler2D uSAMP;
uniform vec3  uLightPos;
uniform vec3  uViewPos;
uniform vec3  uLightColor;

out vec4 fColor;

in vec2 vTexCoor;
in vec3 vNormal;
in vec3 vPos;

void main()
{
	//vec4 color = texture(uSAMP, vTexCoor);
	vec4 color = vec4(0.3, 0.4, 0.3, 1);

	//ambient
	float factor = 0.4f;
	vec3 ambient = factor *  uLightColor;

	//diffuse
	vec3 n = normalize(vNormal);
	vec3 lightDir = normalize(uLightPos - vPos);
	float factor2 = max(dot(n, lightDir), 0);
	vec3 diffuse = factor2 * uLightColor;

	//specular
	float strength = 0.3f;
	vec3 viewDir = normalize(uViewPos - vPos);
	vec3 reflectDir = reflect(-lightDir, n);
	float factor4 =pow(max(dot(reflectDir, viewDir), 0), 4);

	vec3 specular = factor4 * strength * uLightColor;


	vec3 result = (ambient + diffuse + specular) * color;
	
	fColor = vec4(result, 1.0);
}