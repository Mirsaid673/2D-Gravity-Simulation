#include "mesh2D.h"

#include <iostream>

template <class T>
Mesh2D<T>::Mesh2D(const std::vector<T> &v, const std::vector<GLuint> &i)
{
	load(v, i);
}

template <>
void Mesh2D<Vertex2D>::load(const std::vector<Vertex2D> &v, const std::vector<GLuint> &i)
{
	vertices = v;
	indices = i;
	vao.create();
	vbo.create();
	ebo.create();

	vao.bind();

	vbo.set_data(GL_ARRAY_BUFFER, vertices.data(), vertices.size() * sizeof(Vertex2D));
	ebo.set_data(GL_ELEMENT_ARRAY_BUFFER, indices.data(), indices.size() * sizeof(GLuint));

	vao.linkAttrib(0, 2, sizeof(Vertex2D), (GLvoid *)offsetof(Vertex2D, position));
	vao.linkAttrib(1, 2, sizeof(Vertex2D), (GLvoid *)offsetof(Vertex2D, uv));

	vao.unbind();
	vbo.unbind();
	ebo.unbind();
}

template <>
void Mesh2D<ColoredVertex2D>::load(const std::vector<ColoredVertex2D> &v, const std::vector<GLuint> &i)
{
	vertices = v;
	indices = i;
	vao.create();
	vbo.create();
	ebo.create();

	vao.bind();

	vbo.set_data(GL_ARRAY_BUFFER, vertices.data(), vertices.size() * sizeof(ColoredVertex2D));
	ebo.set_data(GL_ELEMENT_ARRAY_BUFFER, indices.data(), indices.size() * sizeof(GLuint));

	vao.linkAttrib(0, 2, sizeof(ColoredVertex2D), (GLvoid *)offsetof(ColoredVertex2D, position));
	vao.linkAttrib(1, 3, sizeof(ColoredVertex2D), (GLvoid *)offsetof(ColoredVertex2D, color));

	vao.unbind();
	vbo.unbind();
	ebo.unbind();
}

template <class T>
Mesh2D<T> Mesh2D<T>::createSquare(const T &p1, const T &p2, const T &p3, const T &p4)
{
	std::vector<T> verts{
		p1,
		p2,
		p3,
		p4,
	};

	std::vector<GLuint> inds{
		0, 1, 2,
		0, 2, 3};

	Mesh2D m(verts, inds);
	return m;
}

template <>
Mesh2D<Vertex2D> Mesh2D<Vertex2D>::createAABB(const glm::vec2 &left_top, const glm::vec2 &right_bottom)
{
	std::vector<Vertex2D> verts{
		Vertex2D{glm::vec2(left_top.x, right_bottom.y), glm::vec2(0, 0)},
		Vertex2D{glm::vec2(left_top.x, left_top.y), glm::vec2(0, 1)},
		Vertex2D{glm::vec2(right_bottom.x, left_top.y), glm::vec2(1, 1)},
		Vertex2D{glm::vec2(right_bottom.x, right_bottom.y), glm::vec2(1, 0)},
	};

	std::vector<GLuint> inds{
		0, 1, 2,
		0, 2, 3};

	Mesh2D m(verts, inds);
	return m;
}

template <>
Mesh2D<ColoredVertex2D> Mesh2D<ColoredVertex2D>::createAABB(const glm::vec2 &left_top, const glm::vec2 &right_bottom, const glm::vec3 &color)
{
	std::vector<ColoredVertex2D> verts{
		ColoredVertex2D{glm::vec2(left_top.x, right_bottom.y), color},
		ColoredVertex2D{glm::vec2(left_top.x, left_top.y), color},
		ColoredVertex2D{glm::vec2(right_bottom.x, left_top.y), color},
		ColoredVertex2D{glm::vec2(right_bottom.x, right_bottom.y), color},
	};

	std::vector<GLuint> inds{
		0, 1, 2,
		0, 2, 3};

	Mesh2D m(verts, inds);
	return m;
}

template <>
Mesh2D<ColoredVertex2D> Mesh2D<ColoredVertex2D>::createCircle(float radius, int quality, const glm::vec3 &color)
{
	GL_TRIANGLE_FAN;
	std::vector<ColoredVertex2D> verts(quality + 2);
	std::vector<GLuint> inds(2 * quality + 1);
	verts[0] = ColoredVertex2D{glm::vec2(0, 0), color};
	inds[0] = 0;
	inds[quality + 1] = 1;

	float angle_offset = 2.0 * M_PI / (double)quality;

	float angle = 0;
	for (int i = 1; i <= quality; i++, angle += angle_offset)
	{
		float x = std::cos(angle) * radius;
		float y = std::sin(angle) * radius;

		verts[i] = ColoredVertex2D{glm::vec2(x, y), color};
		inds[i] = i;
	}

	Mesh2D m(verts, inds);
	m.setMode(GL_TRIANGLE_FAN);
	return m;
}

template <class T>
void Mesh2D<T>::draw() const
{
	vao.bind();
	glDrawElements(mode, indices.size(), GL_UNSIGNED_INT, 0);
}

template <class T>
void Mesh2D<T>::destroy() const
{
	vao.destroy();
	vbo.destroy();
	ebo.destroy();
}

template class Mesh2D<Vertex2D>;
template class Mesh2D<ColoredVertex2D>;