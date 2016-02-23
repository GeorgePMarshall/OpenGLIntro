#version 410

layout(points) in;
layout(triangle_strip, max_vertices = 4) out;

uniform vec3 cameraPos;
uniform mat4 projectionView;

void main()
{
	float halfsize = 4;

	vec3 verticies[4];

	verticies[0] = gl_in[0].gl_Position.xyz + vec3(-halfsize, halfsize, 0);
	verticies[1] = gl_in[0].gl_Position.xyz + vec3(halfsize, halfsize, 0);
	verticies[2] = gl_in[0].gl_Position.xyz + vec3(-halfsize, -halfsize, 0);
	verticies[3] = gl_in[0].gl_Position.xyz + vec3(halfsize, -halfsize, 0);

	mat3 billboard;
	billboard[2] = normalize(cameraPos - gl_in[0].gl_Position.xyz);
	billboard[0] = cross(billboard[2], vec3(0, 1, 0));
	billboard[1] = cross(billboard[2], billboard[0]);


	gl_Position = projectionView * vec4(billboard * verticies[0] , 1);
	EmitVertex();

	gl_Position = projectionView * vec4(billboard * verticies[1] , 1);
	EmitVertex();

	gl_Position = projectionView * vec4(billboard * verticies[2] , 1);
	EmitVertex();

	gl_Position = projectionView * vec4(billboard * verticies[3] , 1);
	EmitVertex();
 

}