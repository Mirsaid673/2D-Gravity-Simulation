#pragma once

#include <GL/glew.h>

class Buffer
{
private:
	GLuint ID;
	GLenum type;

public:
	Buffer() {}
	Buffer(GLenum target, GLvoid *arr, GLuint size);
	void create() {glGenBuffers(1, &ID);}
	void set_data(GLenum target, GLvoid *arr, GLuint size);
	void bind() const;
	void unbind() const;
	void destroy() const;
	GLenum getTarget() const {return type;}
	operator GLuint() const { return ID; }
};