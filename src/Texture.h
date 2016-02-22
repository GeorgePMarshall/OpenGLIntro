#pragma once
#include <GLFW\glfw3.h>
#include <stb\stb_image.h>

class Texture
{
	GLuint textureID;

	GLint width, height;

	GLint imageFormat;


public:
	Texture(const char* filePath);
	~Texture();

	void Bind();


};