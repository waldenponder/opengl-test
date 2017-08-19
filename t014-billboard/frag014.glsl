#version 330 core

uniform sampler2D uSAMP;
uniform vec3  uLightPos;
uniform vec3  uLightColor;

out vec4 fColor;

in vec2 gTexCoor;
in vec3 gNormal;
in vec3 gPos;
in vec3 gViewPos;
in vec3 gTestColor;

void main()
{
	vec4 color = texture(uSAMP, gTexCoor);

	//ambient
	float factor = 0.4f;
	vec3 ambient = factor *  uLightColor;

	//diffuse
	vec3 n = normalize(gNormal);
	vec3 lightDir = normalize(uLightPos - gPos);
	float factor2 = max(dot(n, lightDir), 0);
	vec3 diffuse = factor2 * uLightColor;

	//specular
	float strength = 0.6f;
	vec3 viewDir = normalize(gViewPos - gPos);
	vec3 reflectDir = reflect(-lightDir, n);
	float factor4 = pow(max(dot(reflectDir, viewDir), 0), 128);

	vec3 specular = factor4 * strength * uLightColor;


	vec3 result = (ambient + diffuse + specular) * color.xyz;

	//fColor = vec4(gTestColor, 1);
	fColor = vec4(result, color.a);
}