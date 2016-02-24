#pragma once
#include "ShaderProgram.h"

struct Particle
{
	glm::vec3 position;
	glm::vec3 velocity;
	float lifeSpan;
	float lifeTime;
};



class ParticleEmitter
{
	ShaderProgram drawShader;
	ShaderProgram updateShader;
	
	
	void Initialize();


protected:

	Particle* particles;	
	GLuint maxParticles;
	
	glm::vec3 position;

	float minLifeSpan, maxLifeSpan;
	float startSize, endSize;

	glm::vec4 startColour, EndColour;




public:










};