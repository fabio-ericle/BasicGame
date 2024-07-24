#version 330 core

layout (location = 0) in vec2 aPosition;
layout (location = 1) in vec2 aTexCoords;

out vec2 fTexCoords;
out vec3 fColor;

uniform mat4 projection;
uniform mat4 model;
uniform vec3 aColor;

void main()
{
	gl_Position = projection * model * vec4(aPosition, 0.0, 1.0);
	fTexCoords = aTexCoords;
	fColor = aColor;
}