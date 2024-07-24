#pragma once
#ifndef TEXTURE2D_H
#define TEXTURE2D_H

#include <iostream>
#include <glad/gl.h>

class Texture2D
{
public:
	GLuint textureID;
	GLuint width, height;
	GLuint internalFornat, imageFormat;
	GLuint wrap_s, wrap_t;
	GLuint filterMin, filterMax;

	Texture2D();
	~Texture2D();

	void generate(GLuint width, GLuint height, unsigned char* data);
	void bind() const;
	void unbind() const;
};

#endif // !TEXTURE2D_H


