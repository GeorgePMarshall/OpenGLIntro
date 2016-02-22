#include "MeshRendering.h"

void MeshRendering::Initialize()
{
	camera.LookAt(vec3(15), vec3(0), vec3(0, 1, 0));
	camera.setPerspective(glm::radians(80.f), 16 / 9.f);
	camera.initialize();

	shader.CreateShaderProgram("shaders/Specular.vert", "shaders/Specular.frag");
	
	mesh = new Mesh(&shader, "data/Marksman/Marksman.fbx");
	material = new SpecularMaterial;
	material->SetDiffuse("data/Marksman/Marksman_D.tga");
	material->SetNormal("data/Marksman/Marksman_N.tga");
	material->SetSpecular("data/Marksman/Marksman_S.tga");


	//mesh = new Mesh(&shader, "data/Bunny.fbx");

	
	marksman = glm::scale(marksman, vec3(0.01f));

}

void MeshRendering::Update()
{
	camera.update();
}

void MeshRendering::Draw()
{
	shader.setMat4("projectionView", camera.getProjectionViewTransform());
	shader.setMat4("transform", marksman);
	shader.setFloat("time", (float)glfwGetTime());

	if(Input::getInput()->getKey(GLFW_KEY_F))
		shader.setVec3("light.direction", vec3(sin(glfwGetTime()), sin(glfwGetTime()), sin(glfwGetTime())));
	shader.setVec3("light.diffuse", vec3(1));
	shader.setVec3("light.specular", vec3(1));

	shader.setVec3("cameraPos", camera.getPosition());

	material->Bind(&shader);

	mesh->Draw();
}

void MeshRendering::Shutdown()
{
	delete mesh;
}