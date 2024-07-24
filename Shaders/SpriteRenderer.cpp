#include "SpriteRenderer.h"

SpriteRenderer::SpriteRenderer(Shader& shader) : shader(shader)
{
	this->initRenderData();
}

SpriteRenderer::~SpriteRenderer()
{
	glDeleteVertexArrays(1, &this->VAO);
}

void SpriteRenderer::drawSprite(Texture2D& texture, glm::vec2 position, glm::vec2 size, float rotate, glm::vec3 color)
{
	this->shader.use();
	
	glm::mat4 model = glm::mat4(1.0f);

	model = glm::translate(model, glm::vec3(position, 0.0f));
	model = glm::translate(model, glm::vec3(size.x * 0.5f, size.y * 0.5f, 0.0f));
	model = glm::rotate(model, glm::radians(rotate), glm::vec3(0.0f, 0.0f, 1.0f));
	model = glm::translate(model, glm::vec3(-0.5f * size.x, -0.5f * size.y, 0.0f));
	model = glm::scale(model, glm::vec3(size, 1.0f));

	this->shader.setMat4("model", model);
	this->shader.setVec3("aColor", color);

	glActiveTexture(GL_TEXTURE0);
	texture.bind();

	glBindVertexArray(this->VAO);
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);
}

void SpriteRenderer::initRenderData()
{
	float vertices[] =
	{
		// Position     // Coords
		0.0f, 1.0f,		0.0f, 1.0f,		// Top left
		0.0f, 0.0f,		0.0f, 0.0f,		// Bottom left
		1.0f, 0.0f,		1.0f, 0.0f,		// Bottom right
		1.0f, 1.0f,		1.0f, 1.0f		// Top right

	};

	int indices[] =
	{
		0, 1, 2,
		0, 2, 3
	};

	glGenVertexArrays(1, &this->VAO);
	GLuint VBO;
	glGenBuffers(1, &VBO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glBindVertexArray(this->VAO);
	GLuint position_location = this->shader.getAttribLocation("aPosition");
	GLuint coords_location = this->shader.getAttribLocation("aTexCoords");
	
	glVertexAttribPointer(position_location, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(position_location);

	glVertexAttribPointer(coords_location, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)(2 * sizeof(float)));
	glEnableVertexAttribArray(coords_location);

	glGenBuffers(1, &this->EBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
}

