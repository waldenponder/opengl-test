#version 330 core

uniform sampler2D uSAMP;
uniform vec3 uLightColor;
uniform vec3 uLightPos;
uniform vec3 uViewPos;

out vec4 fColor;

in vec2 vTexCoor;
in vec3 vNormal;
in vec3 vPosition;

void main()
{
	vec3 color = texture(uSAMP, vTexCoor).rgb;

	//vec3 color = vec3(0.5, 0.5, 0.5);

	vec3 Normal = normalize(vNormal);

	//ambient
	vec3 ambient = .4 * uLightColor;
	
	//diffuse
	vec3 lightDir = normalize(uLightPos - vPosition);
	vec3 diffuse = .3 * max(0, dot(lightDir, Normal)) *  uLightColor;

	vec3 specular;

	if (true)
	{
		vec3 eyeDir = normalize(uViewPos - vPosition);
		vec3 middle = normalize(lightDir + eyeDir);
		float strength = max(dot(middle, Normal), 0);
		specular = .5 * pow(strength, 132) * uLightColor;
	}
	else
	{
		vec3 eyeDir = normalize(uViewPos - vPosition);
		vec3 ref = reflect(-lightDir, Normal);
		float strength = max(dot(ref, eyeDir), 0);
		specular = .5 * pow(strength, 128) * uLightColor;
	}

	fColor = vec4((ambient + diffuse + specular) * color, 1);
}