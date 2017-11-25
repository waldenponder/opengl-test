#version 330 core

out vec4 fragColor;

in vec2 texCoor;
in vec3 MCposition;

/*	 Ä¾ÎÆ
vec3 LightWood = vec3(0.827, 0.76, 0.4313);
vec3 DarkWood = vec3(.7, .4, 0.3725);
float RingFreq = 100;
float LightGrains = 1;
float DarkGrains = 1;
vec3 NoiseScale = vec3(1);
float Noisiness = 10;
float GrainScale = 0;
float Lightness = .98;


void main()
{
	vec3 noiseVec = noise3(MCposition * NoiseScale) * Noisiness;
	vec3 location = MCposition + noiseVec;

	float dis = sqrt(location.x * location.x + location.z * location.z);
	dis *= RingFreq;

	float r = fract(dis + noiseVec[0] + noiseVec[1] + noiseVec[2]) * 2;

	if (r > 1) r = 2 - r;

	vec3 color = mix(LightWood, DarkWood, r);

	r = fract((MCposition.x + MCposition.z) * GrainScale + .5);
	noiseVec[2] *= r;

	if (r < GrainScale)
		color += LightWood * LightGrains * noiseVec [2];
	else 
		color -= LightWood * LightGrains * noiseVec[2];

	color *= Lightness;

	fragColor = vec4(color, 1);
}		  */


float LightIntensity = 1;

const vec3 MarbleColor = vec3(0.7, 0.7, 0.7);
const vec3 VeinColor = vec3(0.0, 0.15, 0.0);

uniform sampler3D NoiseTex;
uniform sampler1D SineTex;
vec3 Offset = vec3(100);;

void main(void)
{
	vec3 noisevec = noise3(MCposition + Offset.yzx).xyz; //texture3D(NoiseTex, MCposition + Offset.yzx);

	float intensity = abs(noisevec[0] - 0.25) +
		abs(noisevec[0] - 0.125) +
		abs(noisevec[1] - 0.0625) +
		abs(noisevec[2] - 0.03125);

	//vec4 unswiz = texture1D(SineTex, MCposition.z + intensity * 2.0);
	float sineval = sin(MCposition.z + intensity * 2.0);//.2;// unswiz.s;
	vec3 color = mix(VeinColor, MarbleColor, sineval);
	color *= sineval;
	color = clamp(color, 0.0, 1.0);
	fragColor = vec4(vec3(color), 1.0);
}
