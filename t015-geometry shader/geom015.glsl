#version 330 core
layout(points) in;
layout(triangle_strip, max_vertices = 5) out;

in Varing
{
	vec3 color;
} var[];

out vec3 gColor;

void main()
{
	gColor = var[0].color;
	gl_Position = gl_in[0].gl_Position + vec4(-0.1, -0.1, 0, 0);  //вСоб╫г
	EmitVertex();

	gl_Position = gl_in[0].gl_Position + vec4(0.1, -0.1, 0, 0);	 //сроб╫г
	EmitVertex();

	gl_Position = gl_in[0].gl_Position + vec4(-0.1, 0, 0, 0); //срио╫г
	EmitVertex();
				 
	gl_Position = gl_in[0].gl_Position + vec4(0.1, 0, 0, 0);
	EmitVertex();

	gColor = vec3(1, 1, 1);
	gl_Position = gl_in[0].gl_Position + vec4(0, 0.1, 0, 0);
	EmitVertex();

	EndPrimitive();
}