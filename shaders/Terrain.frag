#version 410

in vec2 vTexCoord;

out vec4 fragColour;


uniform sampler2D heightMap;

void main()
{
	fragColour = texture(heightMap, vTexCoord).rrrr;
	fragColour.a = 1;
}
