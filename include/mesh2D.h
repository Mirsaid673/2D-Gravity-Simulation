#pragma once

#include <vector>
#include <glm/glm.hpp>

#include "VAO.h"
#include "buffer.h"
#include "texture.h"

struct Vertex2D
{
	glm::vec2 position;
	glm::vec2 uv;
};

struct ColoredVertex2D
{
	glm::vec2 position;
	//glm::vec3 color; //color is seted by glAttrib
};

template <class T = Vertex2D>
class Mesh2D
{
private:
	std::vector<T> vertices;
	std::vector<GLuint> indices;
	VAO vao;
	Buffer vbo;
	Buffer ebo;
	GLenum mode = GL_TRIANGLES;

public:
	glm::vec3 color;
	Mesh2D() {}
	Mesh2D(const std::vector<T> &v, const std::vector<GLuint> &i);
	void load(const std::vector<T> &v, const std::vector<GLuint> &i);
	void draw() const;
	void destroy() const;
	void setMode(GLenum m) { mode = m; }

	static Mesh2D<T> createSquare(const T &p1, const T &p2, const T &p3, const T &p4);

	static Mesh2D<Vertex2D> createAABB(const glm::vec2 &left_top, const glm::vec2 &right_bottom);
	static Mesh2D<ColoredVertex2D> createAABB(const glm::vec2 &left_top, const glm::vec2 &right_bottom, const glm::vec3 &color);

	static Mesh2D<ColoredVertex2D> createCircle(float radius, int quality, const glm::vec3 &color);
	static Mesh2D<ColoredVertex2D> createLine();
};