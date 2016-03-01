#include "MeshRendering.h"

void MeshRendering::Initialize()
{
	camera.LookAt(vec3(15), vec3(0), vec3(0, 1, 0));
	camera.setPerspective(glm::radians(80.f), 16 / 9.f);
	camera.initialize();

	shader.CreateShaderProgram("shaders/Specular.vert", "shaders/Specular.frag");
	
	mesh = new Mesh(&shader, "data/soulspear/soulspear.fbx");
	material = new SpecularMaterial;
	material->SetDiffuse("data/soulspear/soulspear_diffuse.tga");
	material->SetNormal("data/soulspear/soulspear_normal.tga");
	material->SetSpecular("data/soulspear/soulspear_specular.tga");
	marksman = glm::scale(marksman, vec3(2));
	

	emitter.Initialize();

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
	
	shader.setVec3("light.direction", vec3(sin(glfwGetTime()), 0.5, cos(glfwGetTime())));
	shader.setVec3("light.diffuse", vec3(1));
	shader.setVec3("light.specular", vec3(1));
	
	shader.setVec3("cameraPos", camera.getPosition());

	material->Bind(&shader);
	mesh->Draw();

	emitter.Draw((Camera*)&camera);
}

void MeshRendering::Shutdown()
{
	delete mesh;
}