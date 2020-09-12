#include <GL/gl.h>
#include "camera.h"

Camera::Camera()
{
	rot_x = rot_y = rot_z = 0.0f;
	x = y = z = 0.0f;
}

void Camera::look()
{
	glRotatef(-rot_x, 1.0f, 0.0f, 0.0f);
	glRotatef(-rot_y, 0.0f, 1.0f, 0.0f);
	glRotatef(-rot_z, 0.0f, 0.0f, 1.0f);
}

void Camera::move()
{
	glTranslatef(x, y, z);
}
