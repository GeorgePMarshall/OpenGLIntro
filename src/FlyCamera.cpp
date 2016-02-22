#include "FlyCamera.h"


void FlyCamera::initialize()
{
	input = Input::getInput();
	time = Time::getInstance();
}

void FlyCamera::update()
{
	vec3 moveDir(0);
	vec3 right = worldTransform[0].xyz;
	vec3 up = worldTransform[1].xyz;
	vec3 forward = worldTransform[2].xyz;

	if (input->getKey(GLFW_KEY_W))
	{
		moveDir -= forward;
	}

	if (input->getKey(GLFW_KEY_S))
	{
		moveDir += forward;
	}

	if (input->getKey(GLFW_KEY_A))
	{
		moveDir -= right;
	}

	if (input->getKey(GLFW_KEY_D))
	{
		moveDir += right;
	}

	if (input->getKey(GLFW_KEY_LEFT_SHIFT))
	{
		moveDir -= up;
	}

	if (input->getKey(GLFW_KEY_SPACE))
	{
		moveDir += up;
	}

	if (glm::length(moveDir))
	{
		moveDir = time->deltaTime() * speed * glm::normalize(moveDir);
		setPosition(getPosition() + moveDir);
	}

	CalculateRotation();

	//LookAt(worldTransform[3].xyz, vec3(0));

}

void FlyCamera::CalculateRotation()
{
	mouseOffset = input->getMousePosition() - oldMousePos;
	oldMousePos = input->getMousePosition();

	if (!glm::length2(mouseOffset)) return;

	if (mouseOffset.y != 0)
	{
		setTransform(getWorldTransform() * glm::rotate(rotateSpeed * time->deltaTime() * -mouseOffset.y, vec3(1, 0, 0)));
	}

	if (mouseOffset.x != 0)
	{
		setTransform(getWorldTransform() * glm::rotate(rotateSpeed * time->deltaTime() * -mouseOffset.x, vec3(viewTransform[1])));
	}

}

