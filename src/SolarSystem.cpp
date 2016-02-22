#include "SolarSystem.h"

void SolarSystem::Initialize()
{
	Gizmos::create();

	camera.LookAt(vec3(15), vec3(0), vec3(0, 1, 0));
	camera.setPerspective(glm::radians(30.f), 16 / 9.f);

	sunMat = glm::mat4();
	earthMatOffset = glm::mat4();
	moonMatOffset = glm::mat4();

	earthMatOffset = glm::translate(earthMatOffset, vec3(5, 0, 5));
	moonMatOffset = glm::translate(moonMatOffset, vec3(1, 0, 1));
}

void SolarSystem::Update()
{	
	sunMat = glm::rotate(sunMat, 0.01f, vec3(0, 1, 0));
	earthMatOffset = glm::rotate(earthMatOffset, -0.02f, vec3(0, 1, 0));
	earthMat = sunMat * earthMatOffset;
	moonMat = earthMat * moonMatOffset;
}

void SolarSystem::Draw()
{
	Gizmos::clear();
	Gizmos::addTransform(glm::mat4(1));

	vec4 white(1);
	vec4 black(0, 0, 0, 1);

	for (int i = 0; i < 21; i++)
	{
		Gizmos::addLine(vec3(-10 + i, 0, 10), vec3(-10 + i, 0, -10), i == 10 ? white : black);
		Gizmos::addLine(vec3(10, 0, -10 + i), vec3(-10, 0, -10 + i), i == 10 ? white : black);
	}

	Gizmos::addSphere(vec3(0), 2, 16, 16, vec4(1, 1, 0, 1), &sunMat);
	Gizmos::addSphere(earthMat[3].xyz, 1, 16, 16, vec4(0, 1, 1, 1), &earthMat);
	Gizmos::addSphere(moonMat[3].xyz, 0.1f, 16, 16, vec4(1, 1, 1, 1), &moonMat);

	Gizmos::draw(camera.getProjectionViewTransform());
}

void SolarSystem::Shutdown()
{

	Gizmos::destroy();
}
