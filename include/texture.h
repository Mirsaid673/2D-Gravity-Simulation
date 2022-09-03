#pragma once

#include <GL/glew.h>

class Texture
{
private:
	GLuint ID;
	int width;
	int height;

public:
	Texture() {}
	Texture(const char *file, GLenum filter = GL_LINEAR);

	void load(const char *file, GLenum filter = GL_LINEAR);
	void load(const unsigned char *data, int w, int h, int num_channel, GLint internalformat = GL_RGBA, GLenum filter = GL_LINEAR);
	void bind() const;
	void unbind() const;
	void use(GLenum unit = GL_TEXTURE0) const;
	void destroy() const;

	int getWidth() const { return width; }
	int getHeight() const { return height; }

	GLuint getID() const { return ID; }
};