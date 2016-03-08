#pragma once
#include <FbxLoader\FBXFile.h>
#include "ShaderProgram.h"
#include <iostream>

class AnimatedMesh
{
	FBXFile* meshData;
	glm::mat4 transform;
	ShaderProgram* shader;


	void CreateBuffers();
	void RemoveBuffers();

public:

	AnimatedMesh(ShaderProgram* shader, const char* filePath);
	~AnimatedMesh();
	void Draw();


};

