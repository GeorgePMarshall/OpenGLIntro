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

in vec4 vNormal;
in vec4 vPosition;
out vec4 fragColour;

uniform float time;
uniform vec3 cameraPos;
uniform dirLight light;
uniform specMaterial material;


vec4 CalcDirLight(dirLight light, vec3 normal, vec3 camPos, vec3 vPos)
{	
	float diffuseTerm = max(0, dot(normal.xyz, light.direction));
	vec3 diffuse = texture(material.diffuse, ) * light.diffuse * diffuseTerm;

	vec3 reflectedVector = reflect(-light.direction, normal.xyz);
	vec3 surfaceToCameraVector = normalize(camPos - vPos);

	float specularTerm = pow(max(0, dot(reflectedVector, surfaceToCameraVector)), 5.0f);
	vec3 specular  = light.specular * vec3(1) * specularTerm;

	return vec4(diffuse + specular, 1);

}


void main()
{
	fragColour = CalcDirLight(light, vNormal.xyz, cameraPos, vPosition.xyz);
}

