#version 330 core
/*
//房子
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
	gl_Position = gl_in[0].gl_Position + vec4(-0.1, -0.1, 0, 0);  //左下角
	EmitVertex();

	gl_Position = gl_in[0].gl_Position + vec4(0.1, -0.1, 0, 0);	 //右下角
	EmitVertex();

	gl_Position = gl_in[0].gl_Position + vec4(-0.1, 0, 0, 0); //右上角
	EmitVertex();
				 
	gl_Position = gl_in[0].gl_Position + vec4(0.1, 0, 0, 0);
	EmitVertex();

	gColor = vec3(1, 1, 1);
	gl_Position = gl_in[0].gl_Position + vec4(0, 0.1, 0, 0);
	EmitVertex();

	EndPrimitive();
}
*/

//贝塞尔曲线
#extension GL_EXT_geometry_shader4 : enable
layout(lines_adjacency) in;
layout(line_strip, max_vertices = 256) out;

in Varing
{
	vec3 color;
} var[];

out Varing
{
	vec3 color;
} varOut;

int num = 30;

void main()
{
	float dt = 1. / float(num);
	float t = .0;

	for (int i = 0; i <= num; i++, t += dt)
	{
		float omt = 1 - t;
		float omt2 = omt * omt;
		float omt3 = omt * omt2;

		float t2 = t * t;
		float t3 = t * t2;

		vec4 val = omt3 * gl_PositionIn[0] + 3. * t * omt2 * gl_PositionIn[1]
			+ 3. * t2 * omt * gl_PositionIn[2] + t3 *  gl_PositionIn[3];

		gl_Position = val;
	
		varOut.color = var[3].color;

		EmitVertex();
	}

}
