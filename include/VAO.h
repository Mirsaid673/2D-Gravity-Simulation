#pragma once

#include <GL/glew.h>

class VAO
{
private:
	GLuint ID;

public:
	void create();
	void bind() const;
	void unbind() const;
	void destroy() const;
	void linkAttrib(GLuint layout, GLuint num_components, GLsizeiptr stride, GLvoid *offset) const;
};