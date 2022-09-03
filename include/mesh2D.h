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

class Mesh2D
{
private:
	std::vector<Vertex2D> vertices;
	std::vector<GLuint> indices;
	VAO vao;
	Buffer vbo;
	Buffer ebo;

public:
	static std::vector<Vertex2D> mulVerts(const std::vector<Vertex2D>&v, glm::vec2 m);
	static const std::vector<Vertex2D> SQUARE_VERT;
	static const std::vector<GLuint> SQUARE_IND;

	Mesh2D() {}
	Mesh2D(const std::vector<Vertex2D> &v, const std::vector<GLuint> &i);
	void load(const std::vector<Vertex2D> &v, const std::vector<GLuint> &i);
	void draw() const;
	void destroy() const;
};