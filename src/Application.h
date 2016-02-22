#pragma once
#include "gl_core_4_4.h"
#include <GLFW\glfw3.h>
#define GLM_SWIZZLE
#include <glm/glm.hpp>
#include <glm/ext.hpp>

class Application
{
private:
	GLFWwindow* window;

public:
	int Run();
	GLFWwindow* GetWindow();

protected:
	virtual void Initialize() = 0;
	virtual void Update() = 0;
	virtual void Draw() = 0;
	virtual void Shutdown() = 0;


};

