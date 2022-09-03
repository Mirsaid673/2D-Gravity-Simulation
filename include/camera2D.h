#pragma once

#include "transform.h"

class Camera2D
{
private:
	glm::mat4 projection;

public:
	Transform transform;
	float width;
	float height;
	float scale = 1.0f;

	Camera2D() : projection(1.0f) {}

	void update();

	const glm::mat4 &getProjection() const { return projection; }
};