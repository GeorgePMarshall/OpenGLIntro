#include "SolarSystem.h"
#include "RenderingTest.h"
#include "MeshRendering.h"

int main()
{
	//SolarSystem* solarSystem = new SolarSystem();
	//int errCode = solarSystem->Run();
	//delete solarSystem;
	//return errCode;

	//RenderingTest* renderingTest = new RenderingTest();
	//int errCode = renderingTest->Run();
	//delete renderingTest;
	//return errCode;

	MeshRendering* meshRendering = new MeshRendering();
	int errCode = meshRendering->Run();
	delete meshRendering;
	return errCode;
}