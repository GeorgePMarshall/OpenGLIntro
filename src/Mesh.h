#pragma once
#include <FbxLoader\FBXFile.h>
#include "ShaderProgram.h"
#include <iostream>

class Mesh
{
	FBXFile* meshData;
	glm::mat4 transform;
	ShaderProgram* shader;


	void CreateBuffers();
	void RemoveBuffers();

public:

	Mesh(ShaderProgram* shader, const char* filePath);
	~Mesh();
	void Draw();


};

