#include "VAO.h"

void VAO::create()
{
	glGenVertexArrays(1, &ID);
}

void VAO::bind() const
{
	glBindVertexArray(ID);
}

void VAO::unbind() const
{
	glBindVertexArray(0);
}

void VAO::destroy() const
{
	glDeleteVertexArrays(1, &ID);
}

void VAO::linkAttrib(GLuint layout, GLuint num_components, GLsizeiptr stride, GLvoid *offset) const
{
	glEnableVertexAttribArray(layout);
	glVertexAttribPointer(layout, num_components, GL_FLOAT, GL_FALSE, stride, offset);
}