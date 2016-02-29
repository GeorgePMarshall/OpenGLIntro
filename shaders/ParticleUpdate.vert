#version 410

layout(location = 0) in vec3 position;
layout(location = 1) in vec3 velocity;
layout(location = 2) in float lifetime;
layout(location = 3) in float lifespan;

out vec3 vPosition;
out vec3 vVelocity;
out float vLifetime;
out float vLifespan;

uniform float time;
uniform float deltatime;

uniform float minLife;
uniform float maxLife;

uniform vec3 emitterPosition;

float rand(float seed, float value)
{
    return fract(sin(dot(vec2(seed, value),vec2(12.9898,78.233))) * 43758.5453);
}

void main()
{
	vPosition = position + velocity * deltatime;
	vVelocity = velocity;
	vLifetime = lifetime + deltatime;
	vLifespan = lifespan;

	if(vLifetime > vLifespan)
	{
		vVelocity = vec3(rand(time, 2) - 1, rand(time, 2) - 1, rand(time, 2) - 1);
		vVelocity = normalize(vVelocity);
		vPosition = emitterPosition;
		vLifetime = 0;
		vLifespan = rand(time, maxLife - minLife) + minLife;
	}

}