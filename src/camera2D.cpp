#include "camera2D.h"

#include <glm/gtc/matrix_transform.hpp>

void Camera2D::update()
{
	float w = width * scale / 2.0f;
	float h = height * scale / 2.0f;
	projection = glm::orthoLH(-w, w,
							  -h, h,
							  -1.0f, 1.0f);
}