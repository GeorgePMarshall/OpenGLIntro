#include "RenderingTest.h"
#include <stb\stb_image.h>
#include "Input.h"
#include "Gizmos.h"

void RenderingTest::Initialize()
{
	Gizmos::create();

	camera.LookAt(vec3(15), vec3(0), vec3(0, 1, 0));
	camera.setPerspective(glm::radians(30.f), 16 / 9.f);
	camera.initialize();

	shader.CreateShaderProgram("Shader.vert", "Shader.frag");

	/*
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);
	glGenVertexArrays(1, &VAO);

	glBindVertexArray(VAO);

	gridVertex = new Vertex[100];

	for (GLuint i = 0; i < 10; ++i)
	{
		for (GLuint j = 0; j < 10; ++j)
		{
			gridVertex[i * 10 + j].position = vec4((float)j, 0, (float)i, 1);
			gridVertex[i * 10 + j].colour = vec4(1.f, 0, 0, 1);
		}
	}
	
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, 100 * sizeof(Vertex), gridVertex, GL_STATIC_DRAW);

	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);

	glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex), 0);
	glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)sizeof(vec4));


	gridIndices = new GLuint[9 * 9 * 6];
	GLuint curIndex = 0;
	
	for (GLuint i = 0; i < 9; ++i)
	{
		for (GLuint j = 0; j < 9; ++j)
		{
			gridIndices[curIndex++] = i * 10 + j;
			gridIndices[curIndex++] =(i + 1) * 10 + j;
			gridIndices[curIndex++] =(i + 1) * 10 + (j + 1);

			gridIndices[curIndex++] = i * 10 + j;
			gridIndices[curIndex++] = (i + 1) * 10 + (j + 1);
			gridIndices[curIndex++] = i * 10 + (j + 1);
		}
	}

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, 9 * 9 * 6 * sizeof(GLuint), gridIndices, GL_STATIC_DRAW);


	glBindVertexArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	
	delete [] gridVertex;
	delete [] gridIndices;
	*/

	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

	GLfloat vertexData[] =
	{
		-5, 0,  5, 1,	0, 1,
		 5, 0,  5, 1,	1, 1,
		 5, 0, -5, 1,	1, 0,
		-5, 0, -5, 1,	0, 0
	};

	GLuint indices[] =
	{
		0, 1, 2,
		0, 2, 3
	};



	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);
	
	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * 24, vertexData, GL_STATIC_DRAW);

	glGenBuffers(1, &EBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(GLuint) * 6, indices, GL_STATIC_DRAW);

	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, sizeof(GLfloat) * 6, 0);
		
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(GLfloat) * 6, (void*)(sizeof(GLfloat) * 4));

	glBindVertexArray(0);
	
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);



	GLint imageWidth, imageHeight, imageFormat;
	GLubyte* texData = stbi_load("data\\awesomeface.png", &imageWidth, &imageHeight, &imageFormat, STBI_default);

	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, imageWidth, imageHeight, 0, GL_RGBA, GL_UNSIGNED_BYTE, texData);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);


	stbi_image_free(texData);

}

void RenderingTest::Update()
{	
	camera.update();
}

void RenderingTest::Draw()
{
	Gizmos::clear();
	Gizmos::addTransform(glm::mat4(1));
	
	for (int i = 0; i < 21; i++)
	{
		Gizmos::addLine(vec3(-10 + i, 0, 10), vec3(-10 + i, 0, -10), i == 10 ? vec4(1) : vec4(0, 0, 0, 1));
		Gizmos::addLine(vec3(10, 0, -10 + i), vec3(-10, 0, -10 + i), i == 10 ? vec4(1) : vec4(0, 0, 0, 1));
	}

	shader.setMat4("projectionView", camera.getProjectionViewTransform());
	shader.setInt("sampler", 0);

	shader.useProgram();

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, texture);

	glBindVertexArray(VAO);
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

	glUseProgram(0);

	Gizmos::draw(camera.getProjectionViewTransform());
}

void RenderingTest::Shutdown()
{
	Gizmos::destroy();
}
