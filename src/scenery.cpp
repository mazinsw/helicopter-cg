#include "scenery.h"
#include <GL/gl.h>

const GLfloat vertexes[4][3] =
{
	{  0.5f,  0.5f,  0.5f},
	{ -0.5f,  0.5f,  0.5f},
	{  0.5f,  0.5f, -0.5f},
	{ -0.5f,  0.5f, -0.5f}
};

void Scenery::load()
{
	tex.load("../res/cenario.rgb", true);
	makeList();
}

void Scenery::makeList()
{
	gl_list = glGenLists(1);
	glNewList(gl_list, GL_COMPILE);
	glEnable(GL_TEXTURE_2D);
	glDisable(GL_DEPTH_TEST); // Disables Depth Testing
	glDisable(GL_LIGHTING);
	glDisable(GL_CULL_FACE);
	glPushMatrix();
	int dist = 100;
	
	glTranslatef(-dist/2.0f, -1.0f, -dist/2.0f);
	glBindTexture(GL_TEXTURE_2D, tex.getId());
	for(int j = 0; j < dist; j++)
	{
		glTranslatef(0.0f, 0.0f, 1.0f);
		for(int i = 0; i < dist; i++)
		{
			glTranslatef(1.0f, 0.0f, 0.0f);
			glBegin(GL_QUADS);
			glTexCoord2f(0.0f, 1.0f);
			glVertex3fv(vertexes[1]);
			glTexCoord2f(1.0f, 1.0f);
			glVertex3fv(vertexes[0]);
			glTexCoord2f(1.0f, 0.0f);
			glVertex3fv(vertexes[2]);
			glTexCoord2f(0.0f, 0.0f);
			glVertex3fv(vertexes[3]);
			glEnd();
		}
		glTranslatef(-dist, 0.0f, 0.0f);
	}
	glPopMatrix();
	glEnable(GL_CULL_FACE);
	glEnable(GL_LIGHTING);
	glEnable(GL_DEPTH_TEST); // Enables Depth Testing
	glEndList();
}
void Scenery::render()
{
	glCallList(gl_list);
}