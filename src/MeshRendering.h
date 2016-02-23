#pragma once
#include "Application.h"
#include "FlyCamera.h"
#include "ShaderProgram.h"
#include "Mesh.h"
#include "SpecularMaterial.h"

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

	GLuint VAO, VBO;

	glm::mat4 marksman;
};