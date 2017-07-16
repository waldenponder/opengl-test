#version 330 core

//uniform sampler2D uSAMP;
uniform sampler2D uDepthTexture;
uniform vec3 uLightColor;
uniform vec3 uLightPos;
uniform vec3 uViewPos;

out vec4 fColor;

in vec2 vTexCoor;
in vec3 vNormal;
in vec3 vPosition;
in vec4 vPosInLightSpace;

void main()
{
	//vec3 color = texture(uSAMP, vTexCoor).rgb;

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

	float shadow = 0.f;
	{
		vec3 projCoords = vPosInLightSpace.xyz / vPosInLightSpace.w;
		// Transform to [0,1] range
		projCoords = projCoords * 0.5 + 0.5;
		// Get closest depth value from light's perspective (using [0,1] range fragPosLight as coords)
		float closestDepth = texture(uDepthTexture, projCoords.xy).r;
		// Get depth of current fragment from light's perspective
		float currentDepth = projCoords.z;
		// Check whether current frag pos is in shadow
		shadow = currentDepth > closestDepth ? 1.0 : 0.0;
		//fColor = texture(uDepthTexture, projCoords.xy);
	}

	fColor = vec4((ambient + (1 - shadow) * (diffuse + specular)) /** color*/, 1);
	//fColor = vec4(shadow);
	fColor = texture(uDepthTexture, vTexCoor);
}