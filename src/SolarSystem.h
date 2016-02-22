#pragma once
#include "Application.h"
#include "Gizmos.h"
#include "Camera.h"

using glm::vec2;
using glm::vec3;
using glm::vec4;


class SolarSystem : public Application
{
private:
	void Initialize() override;
	void Update() override;
	void Draw() override;
	void Shutdown() override;

	Camera camera;

	glm::mat4 sunMat;
	glm::mat4 earthMatOffset;
	glm::mat4 moonMatOffset;
	glm::mat4 earthMat;
	glm::mat4 moonMat;


};