#include "Mesh.h"


Mesh::Mesh(ShaderProgram* shader, const char* filePath)
{
	meshData = new FBXFile();
	meshData->load(filePath);
	CreateBuffers();
	this->shader = shader;
}

Mesh::~Mesh()
{
	RemoveBuffers();
}

void Mesh::CreateBuffers()
{
	for (int i = 0; i < meshData->getMeshCount(); ++i)
	{
		FBXMeshNode* mesh = meshData->getMeshByIndex(i);

		GLuint* bufferData = new GLuint[3];

		std::cout << meshData->getTextureCount();

		glGenVertexArrays(1, &bufferData[0]);
		glBindVertexArray(bufferData[0]);

		glGenBuffers(1, &bufferData[1]);
		glBindBuffer(GL_ARRAY_BUFFER, bufferData[1]);
		glBufferData(GL_ARRAY_BUFFER, mesh->m_vertices.size() * sizeof(FBXVertex), mesh->m_vertices.data(), GL_STATIC_DRAW);

		glGenBuffers(1, &bufferData[2]);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, bufferData[2]);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, mesh->m_indices.size() * sizeof(GLuint), mesh->m_indices.data(), GL_STATIC_DRAW);

		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, sizeof(FBXVertex), 0);

		glEnableVertexAttribArray(1);
		glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, sizeof(FBXVertex), ((char*)0) + FBXVertex::NormalOffset);

		glBindVertexArray(0);
		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

		mesh->m_userData = bufferData;
	}
}
void Mesh::RemoveBuffers()
{
	for (int i = 0; i < meshData->getMeshCount(); ++i)
	{
		FBXMeshNode* mesh = meshData->getMeshByIndex(i);
		GLuint* bufferData = (GLuint*) mesh->m_userData;

		glDeleteVertexArrays(1, &bufferData[0]);
		glDeleteBuffers(1, &bufferData[1]);
		glDeleteBuffers(1, &bufferData[2]);

		delete[] bufferData;
	}
}


void Mesh::Draw()
{
	shader->useProgram();

	for (int i = 0; i < meshData->getMeshCount(); ++i)
	{
		FBXMeshNode* mesh = meshData->getMeshByIndex(i);
		GLuint* bufferData = (GLuint*)mesh->m_userData;
		

		glBindVertexArray(bufferData[0]);
		glDrawElements(GL_TRIANGLES, mesh->m_indices.size(), GL_UNSIGNED_INT, 0);
	}

	
}


