#pragma once

#include "mesh2D.h"
#include "texture.h"
#include "shader.h"
#include "transform.h"

#include <glm/glm.hpp>

class Sprite
{
private:
	Mesh2D mesh;
	Texture texture;

public:
	struct LoadConfguration
	{
		glm::vec2 left_top;
		glm::vec2 right_bottom;
		GLint filter = GL_LINEAR;
	};

	Sprite() {}
	Sprite(const Mesh2D &m, const Texture &t) : mesh(m), texture(t) {}
	Sprite(const char *path, const LoadConfguration &lc);
	Sprite(const char *path);

	void load(const Mesh2D &m, const Texture &t);
	void load(const LoadConfguration &lc, const Texture &t);
	void load(const char *path, const LoadConfguration &lc);
	void load(const char *path);

	~Sprite();

	void draw() const;
	void cleanup();
};