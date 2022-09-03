#include "texture.h"

#include "stb_image.h"

#include <iostream>

Texture::Texture(const char *file, GLenum filter)
{
	load(file, filter);
}

void Texture::load(const char *file, GLenum filter)
{
	int num_channel;
	stbi_set_flip_vertically_on_load(true);
	unsigned char *texture = stbi_load(file, &width, &height, &num_channel, 0);
	if(texture == nullptr)
	{
		std::cerr << "failed to load texture: " << file << std::endl;
	}
	load(texture, width, height, num_channel, GL_RGBA, filter);

	glGenerateMipmap(GL_TEXTURE_2D);

	stbi_image_free(texture);
}

void Texture::load(const unsigned char *data, int w, int h, int num_channel, GLint internalformat, GLenum filter)
{
	width = w;
	height = h;

	glGenTextures(1, &ID);
	glBindTexture(GL_TEXTURE_2D, ID);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, filter);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, filter);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	GLenum format;
	switch (num_channel)
	{
	case 4:
		format = GL_RGBA;
		break;
	case 3:
		format = GL_RGB;
		break;
	case 1:
		format = GL_RED;
		break;
	default:
		glDeleteTextures(1, &ID);
		return;
	}

	glTexImage2D(GL_TEXTURE_2D, 0, internalformat, width, height, 0, format, GL_UNSIGNED_BYTE, data);
}

void Texture::bind() const
{
	glBindTexture(GL_TEXTURE_2D, ID);
}

void Texture::unbind() const
{
	glBindTexture(GL_TEXTURE_2D, 0);
}

void Texture::use(GLenum unit) const
{
	glActiveTexture(unit);
	glBindTexture(GL_TEXTURE_2D, ID);
}

void Texture::destroy() const
{
	glDeleteTextures(1, &ID);
}