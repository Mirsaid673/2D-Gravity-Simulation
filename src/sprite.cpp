#include "sprite.h"

Sprite::Sprite(const char *path, const LoadConfguration &lc)
{
	load(path, lc);
}

Sprite::Sprite(const char *path)
{
	load(path);
}

void Sprite::load(const LoadConfguration &lc, const Texture &t)
{
	texture = t;
	
	std::vector<Vertex2D> v{
		Vertex2D{glm::vec2(lc.left_top.x, lc.right_bottom.y), glm::vec2(0, 0)},
		Vertex2D{glm::vec2(lc.left_top.x, lc.left_top.y), glm::vec2(0, 1)},
		Vertex2D{glm::vec2(lc.right_bottom.x, lc.left_top.y), glm::vec2(1, 1)},
		Vertex2D{glm::vec2(lc.right_bottom.x, lc.right_bottom.y), glm::vec2(1, 0)},
	};

	std::vector<GLuint> i{
		0,
		1,
		2,
		0,
		2,
		3,
	};
	mesh.load(v, i);
}

void Sprite::load(const Mesh2D &m, const Texture &t)
{
	mesh = m;
	texture = t;
}

void Sprite::load(const char *path)
{
	texture.load(path);

	glm::vec2 left_top;
	glm::vec2 right_bottom;

	int w = texture.getWidth();
	int h = texture.getHeight();

	if (w < h)
	{
		float aspect = (float)h / ((float)w * 2);
		left_top.x = -0.5f;
		left_top.y = aspect;
		right_bottom.x = 0.5f;
		right_bottom.y = -aspect;
	}
	else
	{
		float aspect = (float)w / ((float)h * 2);
		left_top.y = 0.5f;
		left_top.x = -aspect;
		right_bottom.y = -0.5f;
		right_bottom.x = aspect;
	}

	std::vector<Vertex2D> v{
		Vertex2D{glm::vec2(left_top.x, right_bottom.y), glm::vec2(0, 0)},
		Vertex2D{glm::vec2(left_top.x, left_top.y), glm::vec2(0, 1)},
		Vertex2D{glm::vec2(right_bottom.x, left_top.y), glm::vec2(1, 1)},
		Vertex2D{glm::vec2(right_bottom.x, right_bottom.y), glm::vec2(1, 0)},
	};

	std::vector<GLuint> i{
		0,
		1,
		2,
		0,
		2,
		3,
	};
	mesh.load(v, i);
}

void Sprite::load(const char *path, const LoadConfguration &lc)
{
	texture.load(path, lc.filter);

	std::vector<Vertex2D> v{
		Vertex2D{glm::vec2(lc.left_top.x, lc.right_bottom.y), glm::vec2(0, 0)},
		Vertex2D{glm::vec2(lc.left_top.x, lc.left_top.y), glm::vec2(0, 1)},
		Vertex2D{glm::vec2(lc.right_bottom.x, lc.left_top.y), glm::vec2(1, 1)},
		Vertex2D{glm::vec2(lc.right_bottom.x, lc.right_bottom.y), glm::vec2(1, 0)},
	};

	std::vector<GLuint> i{
		0,
		1,
		2,
		0,
		2,
		3,
	};
	mesh.load(v, i);
}

void Sprite::draw() const
{
	texture.use(GL_TEXTURE0);
	mesh.draw();
}

Sprite::~Sprite()
{
	texture.destroy();
	mesh.destroy();
}