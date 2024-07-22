#include "Shader.h"
#include <glm/gtc/type_ptr.hpp>

Shader::Shader(const std::string& vertexSource, const std::string& fragmentSource)
{
	const char* vertexSourceCode = vertexSource.c_str();
	const char* fragmentSourceCode = fragmentSource.c_str();

	// Create vertex shader
	GLuint vertex = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertex, 1, &vertexSourceCode, NULL);
	glCompileShader(vertex);
	checkErrors(vertex, "VERTEX");

	// Create fragment shader
	GLuint fragment = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragment, 1, &fragmentSourceCode, NULL);
	glCompileShader(fragment);
	checkErrors(fragment, "FRAGMENT");

	// Create program
	this->programID = glCreateProgram();
	glAttachShader(this->programID, vertex);
	glAttachShader(this->programID, fragment);
	
	glLinkProgram(this->programID);
	checkErrors(this->programID, "PROGRAM");

	// Delete shaders
	glDeleteShader(vertex);
	glDeleteShader(fragment);
}

Shader::~Shader()
{
	glDeleteProgram(this->programID);
}

void Shader::use()
{
	glUseProgram(this->programID);
}

void Shader::setInt(const std::string& name, int value) const
{
	glUniform1i(this->getUniformLocation(name.c_str()), value);
}

void Shader::setBool(const std::string& name, bool value) const
{
	glUniform1i(this->getUniformLocation(name.c_str()), value);
}

void Shader::setFloat(const std::string& name, float value) const
{
	glUniform1f(this->getUniformLocation(name.c_str()), value);
}

void Shader::setVec2(const std::string& name, glm::vec2 value) const
{
	glUniform2f(this->getUniformLocation(name.c_str()), value.x, value.y);
}

void Shader::setVec3(const std::string& name, glm::vec3 value) const
{
	glUniform3f(this->getUniformLocation(name.c_str()), value.x, value.y, value.z);
}

void Shader::setMat4(const std::string& name, glm::mat4 value) const
{
	glUniformMatrix4fv(this->getUniformLocation(name.c_str()), 1, GL_FALSE, glm::value_ptr(value));
}

GLuint Shader::getUniformLocation(std::string name) const
{
	return glGetUniformLocation(this->programID, name.c_str());
}

GLuint Shader::getAttribLocation(std::string name) const
{
	return glGetAttribLocation(this->programID, name.c_str());
}

void Shader::checkErrors(GLuint object, std::string type)
{
	int compileSuccess = 0;
	char infoCompileLog[1024];

	if (type != "PROGRAM")
	{
		glGetShaderiv(object, GL_COMPILE_STATUS, &compileSuccess);
		if (!compileSuccess)
		{
			glGetShaderInfoLog(object, 1024, NULL, infoCompileLog);
			std::cout << "\nERROR::SHADER::" << type << "::FAILED_TO_COMPILE\n" << infoCompileLog << "\n";
		}
	}
	else
	{
		if (type == "PROGRAM")
		{
			glGetProgramiv(object, GL_LINK_STATUS, &compileSuccess);
			if (!compileSuccess)
			{
				glGetProgramInfoLog(object, 1024, NULL, infoCompileLog);
				std::cout << "\nERROR::SHADER::PROGRAM::FAILED_TO_COMPILE\n" << infoCompileLog << "\n";
			}
			else
			{
				std::cout << "\nERROR::SHADER::WRONG_TYPE\n";
			}
		}
	}
}