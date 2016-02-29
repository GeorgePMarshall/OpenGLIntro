#pragma once
#include "Application.h"
#include "FlyCamera.h"
#include "ShaderProgram.h"
#include "Mesh.h"
#include "SpecularMaterial.h"
#include "ParticleEmitter.h"

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

	GLuint VAO, VBO;

	glm::mat4 marksman;
};