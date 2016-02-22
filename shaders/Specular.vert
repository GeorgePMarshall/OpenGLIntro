
#version 410

layout(location = 0) in vec4 position;
layout(location = 1) in vec4 normal;

out vec4 vNormal;
out vec4 vPosition;

uniform mat4 projectionView;
uniform mat4 transform;

void main() 
{
	vNormal = normal;
	vPosition = position;
	gl_Position = projectionView * transform * position;
}

