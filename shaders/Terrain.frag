#version 410

struct specMaterial
{
	sampler2D diffuse;
	sampler2D normal;
	sampler2D specular;
	float specPow;
};

struct dirLight
{
	vec3 direction;
	vec3 diffuse;
	vec3 specular;
};

in vec3 vPosition;
in vec3 vNormal;
in vec2 vTexCoord;

out vec4 fragColour;

uniform sampler2D heightMap;
uniform specMaterial material;
uniform dirLight light;
uniform vec3 camPos;

void main()
{
	//fragColour = texture(heightMap, vTexCoord).rrrr / 5;
	//fragColour.a = 1;

	float diffuseTerm = max(0, dot(vNormal, normalize(light.direction)));
	vec3 diffuse = vec3(texture(material.diffuse, vTexCoord)) * light.diffuse * diffuseTerm;

	vec3 reflectedVector = reflect(-light.direction, vNormal);
	vec3 surfaceToCameraVector = normalize(camPos - vPosition);

	float specularTerm = pow(max(0, dot(reflectedVector, surfaceToCameraVector)), 1.0f);
	vec3 specular = light.specular * texture(material.specular, vTexCoord).xyz * specularTerm;




	fragColour = mix (vec4(diffuse + specular, 1), texture(heightMap, vTexCoord).rrrr, 0.00);
	//fragColour = CalcDirLight(light, vNormal, camPos, vPosition);
}
