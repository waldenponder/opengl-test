#version 330 core
out vec4 color;
in vec2 Coor;
uniform sampler2D samp;

void main()
{
    //vec4 tmp = texture(samp, Coor);
    color = texture2D(samp, Coor);
    //float average = (color.r + color.g + color.b) / 3.0;
   // color = vec4(average, average, average, 1.0);

/* 
  const float offset = 1.0 / 300;

  	vec2 offsets[9] = vec2[](
		vec2(-offset, offset),  // top-left
		vec2(0.0f, offset),  // top-center
		vec2(offset, offset),  // top-right
		vec2(-offset, 0.0f),    // center-left
		vec2(0.0f, 0.0f),    // center-center
		vec2(offset, 0.0f),    // center-right
		vec2(-offset, -offset), // bottom-left
		vec2(0.0f, -offset), // bottom-center
		vec2(offset, -offset)  // bottom-right
		);

	float kernel[9] = float[](
		-1, -1, -1,
		-1, 9, -1,
		-1, -1, -1
		);

	vec3 sampleTex[9];
	for (int i = 0; i < 9; i++)
	{
		sampleTex[i] = vec3(texture(samp, Coor.st + offsets[i]));
	}
	vec3 col;
	for (int i = 0; i < 9; i++)
		col += sampleTex[i] * kernel[i];

	color = vec4(col, 1.0);*/
}