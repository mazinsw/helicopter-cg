#include "util.h"
#include <GL/gl.h>

void drawCube()
{
	const GLfloat vertexes[8][3] =
	{
		{ -0.5f, -0.5f,  0.5f},
		{  0.5f, -0.5f,  0.5f},
		{  0.5f,  0.5f,  0.5f},
		{ -0.5f,  0.5f,  0.5f},
		{ -0.5f, -0.5f, -0.5f},
		{  0.5f, -0.5f, -0.5f},
		{  0.5f,  0.5f, -0.5f},
		{ -0.5f,  0.5f, -0.5f}
	};

	const GLfloat normals[6][3] =
	{
		{  0.0,  0.0,  2.0 },
		{  0.0,  0.0, -2.0 },
		{  0.0, -2.0,  0.0 },
		{  0.0,  2.0,  0.0 },
		{  2.0,  0.0,  0.0 },
		{ -2.0,  0.0,  0.0 }
	};

	glBegin(GL_QUADS);

	// Front face
	glNormal3fv(normals[0]);
	glVertex3fv(vertexes[0]);
	glVertex3fv(vertexes[1]);
	glVertex3fv(vertexes[2]);
	glVertex3fv(vertexes[3]);

	// Back face
	glNormal3fv(normals[1]);
	glVertex3fv(vertexes[5]);
	glVertex3fv(vertexes[4]);
	glVertex3fv(vertexes[7]);
	glVertex3fv(vertexes[6]);

	// Top face
	glNormal3fv(normals[2]);
	glVertex3fv(vertexes[4]);
	glVertex3fv(vertexes[5]);
	glVertex3fv(vertexes[1]);
	glVertex3fv(vertexes[0]);

	// Bottom face
	glNormal3fv(normals[3]);
	glVertex3fv(vertexes[3]);
	glVertex3fv(vertexes[2]);
	glVertex3fv(vertexes[6]);
	glVertex3fv(vertexes[7]);

	// Right face
	glNormal3fv(normals[4]);
	glVertex3fv(vertexes[1]);
	glVertex3fv(vertexes[5]);
	glVertex3fv(vertexes[6]);
	glVertex3fv(vertexes[2]);

	// Left face
	glNormal3fv(normals[5]);
	glVertex3fv(vertexes[4]);
	glVertex3fv(vertexes[0]);
	glVertex3fv(vertexes[3]);
	glVertex3fv(vertexes[7]);

	glEnd();
}

void drawAxis()
{
	// eixo x
	glColor3f(1.0f, 0.0f, 0.0f);
	glBegin(GL_LINES);
	glVertex3f(-5.0f, 0.0f, 0.0f);
	glVertex3f( 5.0f, 0.0f, 0.0f);
	glEnd();

	// eixo y
	glColor3f(0.0f, 1.0f, 0.0f);
	glBegin(GL_LINES);
	glVertex3f(0.0f, -5.0f, 0.0f);
	glVertex3f(0.0f,  5.0f, 0.0f);
	glEnd();

	// eixo z
	glColor3f(0.0f, 0.0f, 1.0f);
	glBegin(GL_LINES);
	glVertex3f(0.0f, 0.0f, -5.0f);
	glVertex3f(0.0f, 0.0f,  5.0f);
	glEnd();
}
