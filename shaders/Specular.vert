#version 410

layout(location = 0) in vec4 position;
layout(location = 1) in vec4 normal;
layout(location = 2) in vec4 tangent;
layout(location = 3) in vec4 biTangent;
layout(location = 4) in vec2 texCoords;

out vec4 vNormal;
out vec4 vPosition;
out vec4 vTangent;
out vec4 vBiTangent;
out vec2 vTexCoords;

uniform mat4 projectionView;
uniform mat4 transform;

void main() 
{
	vNormal = normal;
	vPosition = position;
	vTangent = tangent;
	vBiTangent = biTangent;
	vTexCoords = texCoords;

	gl_Position = projectionView * transform * position;
}

