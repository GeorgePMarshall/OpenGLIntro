#include "MeshRendering.h"

void MeshRendering::Initialize()
{
	camera.LookAt(vec3(15), vec3(0), vec3(0, 1, 0));
	camera.setPerspective(glm::radians(80.f), 16 / 9.f);
	camera.initialize();

	shader.CreateShaderProgram("animatedSpecular.vert", "animatedSpecular.frag");
	
	transform = glm::translate(transform, vec3(10));
	transform = glm::scale(transform, vec3(0.2));
	transform = glm::rotate(transform, glm::radians(-90.f) , vec3(1, 0, 0));

	dragon = new AnimatedMesh(&shader, "data/demolition/demolition.fbx");
	
	//terrain.Initialize(100, 100);

	//emitter.Initialize();

}

void MeshRendering::Update()
{
	if (Input::getInput()->getKey(GLFW_KEY_T))
	{
		++i;
		if (i >= cats.size())
			i = 0;
		camera.setWorldTransform(cats[i]);
	}
	else if(Input::getInput()->getKey(GLFW_KEY_R))
	{
		camera.update();
		cats.push_back(camera.getWorldTransform());
	}
	else
	{
		camera.update();
	}
}

void MeshRendering::Draw()
{
	shader.setMat4("projectionView", camera.getProjectionViewTransform());
	shader.setMat4("transform", transform);
	shader.setFloat("time", (float)glfwGetTime());
	
	shader.setVec3("light.direction", vec3(0.2));
	shader.setVec3("light.diffuse", vec3(1));
	shader.setVec3("light.specular", vec3(1));
	
	shader.setVec3("cameraPos", camera.getPosition());

	dragon->Draw();

	//emitter.Draw((Camera*)&camera);
	

	//terrain.draw((Camera*)&camera);
}

void MeshRendering::Shutdown()
{
	delete dragon;
}