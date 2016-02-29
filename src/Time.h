#pragma once
#include <GLFW\glfw3.h>


class Time
{
private:
	static Time* timeInstance;
	float dt;
	float curTime;
	float prevTime;


public:

	static void Initialize();
	static Time* getInstance();

	void Update();

	static float deltaTime();


};
