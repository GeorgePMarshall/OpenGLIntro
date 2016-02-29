#pragma once
#include "Camera.h"
#include "Input.h"
#include "Time.h"



class FlyCamera : public Camera
{
	Input* input;

	GLfloat speed = 5.0f;
	GLfloat rotateSpeed = 0.01f;
	vec2 mouseOffset, oldMousePos;

	void CalculateRotation();


public:
	void initialize() override;
	void update() override;


};