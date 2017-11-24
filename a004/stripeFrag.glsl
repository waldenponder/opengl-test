#version 330 core

out vec4 fragColor;
in vec2 texCoor;
in vec2 MCposition;

vec3 stripeColor = vec3(1, 0, 0);
vec3 backColor = vec3(1, 1, 0);

float width = 1;
float fuzz = .8;
float scale = 10;

uniform sampler2D SAMP;

void main()
{
	float scaleT = fract(texCoor.t * scale);
	float fract1 = clamp(scaleT / fuzz, 0, 1);
	float fract2 = clamp((scaleT - width) / fuzz, 0, 1);

	fract1 = fract1 * (1 - fract2);
	fract1 = fract1 * fract1 * (3 - (2 * fract1) );

	vec3 color = mix(backColor, stripeColor, fract1);
	fragColor = vec4(color, 1);
}