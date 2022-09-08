#include "camera2D.h"

#include <glm/gtc/matrix_transform.hpp>

void Camera2D::update()
{
	updateKeep();
}

void Camera2D::updateKeep()
{
	if (width > height)
	{
		width /= height;
		height = 1.0f;
	}
	else
	{
		height /= width;
		width = 1;
	}

	float w = width * scale / 2.0f;
	float h = height * scale / 2.0f;

	projection = glm::orthoLH(-w, w,
							  -h, h,
							  -1.0f, 1.0f);
}

void Camera2D::updateKeepWidth()
{
	height /= width;
	width = 1;

	float w = width * scale / 2.0f;
	float h = height * scale / 2.0f;

	projection = glm::orthoLH(-w, w,
							  -h, h,
							  -1.0f, 1.0f);
}

void Camera2D::updateKeepHeight()
{
	width /= height;
	height = 1.0f;

	float w = width * scale / 2.0f;
	float h = height * scale / 2.0f;

	projection = glm::orthoLH(-w, w,
							  -h, h,
							  -1.0f, 1.0f);
}