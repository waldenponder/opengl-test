#version 330 core

out vec4 fragColor;
in vec2 texCoor;
in vec2 MCposition;

vec3 brickColor = vec3(.8, .2, .2);
vec3 mortarColor = vec3(.7);
vec2 brickPct = vec2(.9);
vec2 brickSize = vec2(30);

float LightIntensity = 1;

uniform sampler2D SAMP;

void main()
{
	vec3 baseColor = texture(SAMP, texCoor).xyz * .01;
	mortarColor = texture(SAMP, vec2(.5)).xyz;

	vec3 color;
	vec2 position, useBrick;
	
	position = MCposition * 100 / brickSize;
	
	if(fract(position.y * .5) > .5)
       position.x += .5;
   
    position = fract(position);
	
	useBrick = step(position, brickPct);
	
	color = mix(mortarColor, brickColor, useBrick.x * useBrick.y);
	
	color *= LightIntensity;

	color += baseColor;
	fragColor = vec4(color, 1);
}