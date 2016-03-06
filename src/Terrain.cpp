#include "Terrain.h"
#include "Time.h"

void Terrain::Initialize(GLuint rows, GLuint cols)
{
	this->rows = rows;
	this->cols = cols;
	
	shader.CreateShaderProgram("Terrain.vert", "Terrain.frag");
	
	heightMap = new Texture;

	GenerateGrid();
	GenerateHeightMap();
}


void Terrain::GenerateGrid()
{
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);

	Vertex* vertices = new Vertex[rows * cols];
	for (GLuint i = 0; i < rows; ++i)
	{
		for (GLuint j = 0; j < cols; ++j)
		{
			vertices[i * cols + j].position = vec3((float)j, 0, (float)i);
			vertices[i * cols + j].texCoord = vec2((float)j/rows, (float)i/cols);
		}
	}

	glBindVertexArray(VAO);
	
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, (rows * cols) * sizeof(Vertex), vertices, GL_STATIC_DRAW);

	glEnableVertexAttribArray(0); //position
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), 0);
	glEnableVertexAttribArray(1); //texCoord 
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)sizeof(vec3));


	GLuint* indices = new GLuint[(rows - 1) * (cols - 1) * 6];
	GLuint curIndex = 0;
	for (GLuint i = 0; i < (rows - 1); ++i)
	{
		for (GLuint j = 0; j < (cols - 1); ++j)
		{
			indices[curIndex++] = i * cols + j;
			indices[curIndex++] = (i + 1) * cols + j;
			indices[curIndex++] = (i + 1) * cols + (j + 1);

			indices[curIndex++] = i * cols + j;
			indices[curIndex++] = (i + 1) * cols + (j + 1);
			indices[curIndex++] = i * cols + (j + 1);
		}
	}

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, (rows - 1) * (cols - 1) * 6 * sizeof(GLuint), indices, GL_STATIC_DRAW);


	glBindVertexArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

	delete[] vertices;
	delete[] indices;
}

void Terrain::GenerateHeightMap()
{
	GLfloat* perlinData = new GLfloat[rows * cols];
	GLfloat scale = (1.f / cols) * 3;
	//GLfloat scale = (i * 0.99853f - j * 0.05408f);
	GLuint sampleAmount = 6;
	GLfloat amplitudeStep = 0.3f;
	
	for (GLuint i = 0; i < rows; ++i)
	{
		for (GLuint j = 0; j < cols; ++j)
		{
			GLfloat amplitude = 1.f;
			perlinData[j * cols + i] = 0;

			for (GLuint k = 0; k < sampleAmount; ++k)
			{
				GLfloat frequency = powf(6, (float)k);
				GLfloat perlinSample = glm::perlin(vec2(i, j) * scale * frequency) * 0.5 + 0.5;
				perlinData[j * cols + i] += perlinSample * amplitude;
				amplitude *= amplitudeStep;
			}
		}
	}

	heightMap->LoadTexture(perlinData, rows, cols, GL_R32F, GL_RED);
	delete[] perlinData;
}

void Terrain::draw(Camera* camera)
{
	shader.setMat4("projectionView", camera->getProjectionViewTransform());

	shader.useProgram();
	glBindVertexArray(VAO);

	glActiveTexture(GL_TEXTURE0);
	shader.setFloat("heightMap", 0);
	heightMap->Bind();
	
	glDrawElements(GL_TRIANGLES, (rows - 1) * (cols - 1) * 6, GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);


}