#version 330 core
out vec4 color;

in vec3 vert_color;
in vec2 texCoor;
uniform vec4 myColor;

uniform sampler2D sampler;
uniform sampler2D sampler2;

void main()
{
  color = mix(texture(sampler, texCoor), texture(sampler2, texCoor), 0.5);
  //vec4(texCoor, 0, 1);
  /*vec4(vert_color, 1)*/
  /*vec4(1.0f, 0.5f, 0.5f, 1.0f) myColor */
}