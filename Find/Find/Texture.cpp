#include "Texture.h"

Texture::Texture()
	: _width(0)
	, _height(0)
{
}

Texture::Texture(float* data, int width, int height)
	: _width(width)
	, _height(height)
{
	glGenTextures(1, &_texId);
	bind();
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_R32F, width, height, 0, GL_RED, GL_FLOAT, data);
	unbind();
}

Texture::~Texture()
{
	glDeleteTextures(1, &_texId);
}

inline void Texture::bind()
{
	glBindTexture(GL_TEXTURE_2D, _texId);
}

inline void Texture::unbind()
{
	glBindTexture(GL_TEXTURE_2D, 0);
}

void Texture::updateData(float* updatedData)
{
	bind();
	glTexSubImage2D(GL_TEXTURE_2D, 0, 0, 0, _width, _height, GL_RED, GL_FLOAT, updatedData);
	unbind();
}
