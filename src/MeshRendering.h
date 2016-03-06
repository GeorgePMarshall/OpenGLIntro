#pragma once
#include "Application.h"
#include "FlyCamera.h"
#include "ShaderProgram.h"
#include "Mesh.h"
#include "SpecularMaterial.h"
#include "ParticleEmitter.h"
#include "Terrain.h"
#include <vector>

class MeshRendering : public Application
{
	void Initialize() override;
	void Update() override;
	void Draw() override;
	void Shutdown() override;

	FlyCamera camera;
	ShaderProgram shader;

	Mesh* mesh;
	SpecularMaterial* material;
	ParticleEmitter emitter;
	Terrain terrain;

	GLuint VAO, VBO;

	glm::mat4 marksman;
	std::vector<glm::mat4> cats;
	int i = 0;
};