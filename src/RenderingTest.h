#pragma once
#include "Application.h"
#include "FlyCamera.h"
#include "ShaderProgram.h"
#include "Time.h"

using glm::vec2;
using glm::vec3;
using glm::vec4;

class RenderingTest : public Application
{
private:
	void Initialize() override;
	void Update() override;
	void Draw() override;
	void Shutdown() override;

	FlyCamera camera;
	ShaderProgram shader;

	//Vertex* gridVertex;
	GLuint* gridIndices;
	GLuint VAO, VBO, EBO;

	GLuint texture;

};