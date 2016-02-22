#include "Time.h"

Time* Time::timeInstance = nullptr;


void Time::Initialize()
{
	if (timeInstance == nullptr)
	{
		timeInstance = new Time;
	}
}

void Time::Update()
{
	curTime = (float)glfwGetTime();
	dt = curTime - prevTime;
	prevTime = curTime;
}

float Time::deltaTime()
{
	return dt;
}

Time* Time::getInstance()
{
	return timeInstance;
}