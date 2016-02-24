#include "ParticleEmitter.h"


void ParticleEmitter::Initialize()
{
	drawShader.CreateShaderProgram("ParticleDraw.vert", "ParticleDraw.geom", "ParticleDraw.frag");
	updateShader.CreateShaderProgram("ParticleUpdate.vert");
}
