#pragma once
#ifndef SHADER_H
#define SHADER_H

#include <iostream>
#include <glad/gl.h>
#include <glm/glm.hpp>

class Shader
{
public:
	GLuint programID;

	Shader(const std::string& vertexSource, const std::string& fragmentSource);
	~Shader();

	void use();

	void setInt(const std::string& name, int value) const;
	void setBool(const std::string& name, bool value) const;
	void setFloat(const std::string& name, float value) const;
	void setVec2(const std::string& name, glm::vec2 value) const;
	void setVec3(const std::string& name, glm::vec3 value) const;
	void setMat4(const std::string& name, glm::mat4 value) const;
	GLuint getUniformLocation(std::string name) const;
	GLuint getAttribLocation(std::string name) const;

private:
	void checkErrors(GLuint object, std::string type);
};

#endif // !SHADER_H


