#include "MeshRendering.h"

void MeshRendering::Initialize()
{
	camera.LookAt(vec3(15), vec3(0), vec3(0, 1, 0));
	camera.setPerspective(glm::radians(80.f), 16 / 9.f);
	camera.initialize();

	//shader.CreateShaderProgram("shaders/Specular.vert", "shaders/Specular.frag");
	shader.CreateShaderProgram("shaders/Particle.vert", "shaders/Particle.geom", "shaders/Particle.frag");
	
	mesh = new Mesh(&shader, "data/soulspear/soulspear.fbx");
	material = new SpecularMaterial;
	material->SetDiffuse("data/soulspear/soulspear_diffuse.tga");
	material->SetNormal("data/soulspear/soulspear_normal.tga");
	material->SetSpecular("data/soulspear/soulspear_specular.tga");

	GLfloat vertexData[] =
	{
		0, 0, 0,

		4, 4, 4
	};


	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * 6, vertexData, GL_STATIC_DRAW);

	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(GLfloat) * 3, 0);

	glBindBuffer(GL_ARRAY_BUFFER, 0);


	
	marksman = glm::scale(marksman, vec3(2));

}

void MeshRendering::Update()
{
	camera.update();
}

void MeshRendering::Draw()
{
	shader.setMat4("projectionView", camera.getProjectionViewTransform());
	//shader.setMat4("transform", marksman);
	shader.setFloat("time", (float)glfwGetTime());


	//shader.setVec3("light.direction", vec3(sin(glfwGetTime()), 0.5, cos(glfwGetTime())));
	//shader.setVec3("light.diffuse", vec3(1));
	//shader.setVec3("light.specular", vec3(1));

	shader.setVec3("cameraPos", camera.getPosition());
	
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glDrawArrays(GL_POINTS, 0, 2);

	//material->Bind(&shader);

	//mesh->Draw();
}

void MeshRendering::Shutdown()
{
	delete mesh;
}