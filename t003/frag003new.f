#version 330 core
out vec4 color;
in vec2 Coor;
uniform sampler2D sampNew;
/*
void main()
{
  vec4 tmp = texture(sampNew, Coor);

  color = tmp.rgba;
  //color = vec4(Coor, 0, 1);

  //float average = (color.r + color.g + color.b) / 3.0;
  //color = vec4(average, average, average, 1.0);
}*/

const float offset = 1.0 / 70;  
 
void main()
{
    vec2 offsets[9] = vec2[](
        vec2(-offset, offset),  // top-left
        vec2(0.0f,    offset),  // top-center
        vec2(offset,  offset),  // top-right
        vec2(-offset, 0.0f),    // center-left
        vec2(0.0f,    0.0f),    // center-center
        vec2(offset,  0.0f),    // center-right
        vec2(-offset, -offset), // bottom-left
        vec2(0.0f,    -offset), // bottom-center
        vec2(offset,  -offset)  // bottom-right    
    );
 
    float kernel[9] = float[](
        -1, -1, -1,
        -1,  9, -1,
        -1, -1, -1
    );
    
    vec3 sampleTex[9];
    for(int i = 0; i < 9; i++)
    {
        sampleTex[i] = vec3(texture(sampNew, Coor.st + offsets[i]));
    }
    vec3 col = vec3(0.0); //原文为vec3 col; 叶大指出错误
 
    for(int i = 0; i < 9; i++)
        col += sampleTex[i] * kernel[i];
    
    color = vec4(col, 1.0);
	//color = texture(sampNew, Coor);
	//float average = 0.2126 * color.r + 0.7152 * color.g + 0.0722 * color.b;
	//color = vec4(average, average, average, 1.0);
}