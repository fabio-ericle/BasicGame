#version 330 core

out vec4 color;

in vec2 fTexCoords;
in vec3 fColor;

uniform sampler2D fTexture;

void main()
{
	color = texture(fTexture, fTexCoords) * vec4(fColor, 1.0);
}