#include "ShaderProgram.h"
#include <fstream>
#include <string>
#include <sstream>
#include <iostream>


void ShaderProgram::CreateShaderProgram(const char* vertexShaderPath, const char* fragmentShaderPath)
{
	std::string vertexShaderSource, fragmentShaderSource;
	std::ostringstream vertexShaderStream, fragmentShaderStream;

	std::ifstream vertexShaderFile(vertexShaderPath);
	std::ifstream fragmentShaderFile(fragmentShaderPath);

	vertexShaderStream << vertexShaderFile.rdbuf();
	fragmentShaderStream << fragmentShaderFile.rdbuf();

	vertexShaderSource = vertexShaderStream.str();
	fragmentShaderSource = fragmentShaderStream.str();

	vertexShaderFile.close();
	fragmentShaderFile.close();
	

	//Vertex Shader creation
	GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
	const GLchar* vertexShaderCharSource = vertexShaderSource.c_str();
	glShaderSource(vertexShader, 1, &vertexShaderCharSource, 0);
	glCompileShader(vertexShader);
	GLint vertexSuccess = GL_FALSE;
	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &vertexSuccess);
	if (vertexSuccess == GL_FALSE)
	{
		int infoLogLength = 0;
		glGetShaderiv(vertexShader, GL_INFO_LOG_LENGTH, &infoLogLength);
		GLchar* infoLog = new char[infoLogLength];
	
		glGetShaderInfoLog(vertexShader, infoLogLength, 0, infoLog);
		std::cout << "Vertex shader creation failed: \n" << infoLog << '\n';
	
		delete[] infoLog;
	}

	//Fragment Shader creation
	GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	const GLchar* fragmentShaderCharSource = fragmentShaderSource.c_str();
	glShaderSource(fragmentShader, 1, &fragmentShaderCharSource, 0);
	glCompileShader(fragmentShader);
	GLint fragmentSuccess = GL_FALSE;
	glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &fragmentSuccess);
	if (fragmentSuccess == GL_FALSE)
	{
		int infoLogLength = 0;
		glGetShaderiv(fragmentShader, GL_INFO_LOG_LENGTH, &infoLogLength);
		GLchar* infoLog = new char[infoLogLength];
	
		glGetShaderInfoLog(fragmentShader, infoLogLength, 0, infoLog);
		std::cout << "Fragment shader creation failed: \n" << infoLog << '\n';
	
		delete[] infoLog;
	}

	//Program Creation and linking
	programID = glCreateProgram();
	glAttachShader(programID, vertexShader);
	glAttachShader(programID, fragmentShader);
	glLinkProgram(programID);

	GLint programSuccess = GL_FALSE;
	glGetProgramiv(programID, GL_LINK_STATUS, &programSuccess);
	if (programSuccess == GL_FALSE)
	{
		int infoLogLength = 0;
		glGetProgramiv(programID, GL_INFO_LOG_LENGTH, &infoLogLength);
		GLchar* infoLog = new char[infoLogLength];
	
		glGetProgramInfoLog(programID, infoLogLength, 0, infoLog);
		std::cout << "Failed to link shader program: \n" << infoLog << '\n';
		
		delete[] infoLog;
	}

	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);

}

void ShaderProgram::useProgram()
{
	glUseProgram(programID);
}


void ShaderProgram::setInt(const char* name, GLint value)
{
	useProgram();
	glUniform1i(glGetUniformLocation(programID, name), value);
}
void ShaderProgram::setFloat(const char* name, GLfloat value)
{
	useProgram();
	glUniform1f(glGetUniformLocation(programID, name), value);
}
void ShaderProgram::setVec2(const char* name, const glm::vec2 &value)
{
	useProgram();
	glUniform2f(glGetUniformLocation(programID, name), value.x, value.y);
}
void ShaderProgram::setVec3(const char* name, const glm::vec3 &value)
{
	useProgram();
	glUniform3f(glGetUniformLocation(programID, name), value.x, value.y, value.z);
}
void ShaderProgram::setVec4(const char* name, const glm::vec4 &value)
{
	useProgram();
	glUniform4f(glGetUniformLocation(programID, name), value.x, value.y, value.z, value.w);
}
void ShaderProgram::setMat4(const char* name, const glm::mat4 &value)
{
	useProgram();
	glUniformMatrix4fv(glGetUniformLocation(programID, name), 1, GL_FALSE, glm::value_ptr(value));
}


