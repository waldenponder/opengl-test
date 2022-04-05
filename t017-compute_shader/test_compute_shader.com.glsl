#version 430
layout (local_size_x = 256, local_size_y = 1, local_size_z = 1 ) in;

uniform int u_num;

uniform layout( binding = 0, r32f) imageBuffer buf;

void main()
{
	uint thxId = gl_GlobalInvocationID.x;
	if( thxId >= u_num )
		return;

    float val = thxId * 2 + 1;
	for(int j = 0; j < 1000; j++)
	   val = sqrt(val+7);
	imageStore( buf, int(thxId), vec4(val,0,0,0) );
	//imageStore( buf, 2, uvec4(103, 0, 0, 0) );
}