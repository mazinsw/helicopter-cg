#include "skybox.h"
#include <GL/gl.h>
#include <gl/glext.h>

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

void SkyBox::load()
{
	const char* tex_name[] =
	{
		"../res/front.rgb",
		"../res/back.rgb",
		"../res/top.rgb",
		"../res/bottom.rgb",
		"../res/right.rgb",
		"../res/left.rgb"
	};
	for(int i = 0; i < 6; i++)
	{
		tex[i].load(tex_name[i], true);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);	//we repeat the pixels in the edge of the texture, it will hide that 1px wide line at the edge of the cube, which you have seen in the video
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);	//we do it for vertically and horizontally (previous line)
	}
}

void SkyBox::render()
{
	glEnable(GL_TEXTURE_2D);
	glDisable(GL_DEPTH_TEST); // Disables Depth Testing
	glDisable(GL_LIGHTING);
	glDisable(GL_CULL_FACE);
	glPushMatrix();
	glScalef(50.0f, 50.0f, 50.0f);
	glRotatef(180, 1.0f, 0.0f, 0.0f);
	// Front face
	glBindTexture(GL_TEXTURE_2D, tex[0].getId());
	glBegin(GL_QUADS);
	glTexCoord2f(0.0f, 1.0f);
	glVertex3fv(vertexes[0]);
	glTexCoord2f(1.0f, 1.0f);
	glVertex3fv(vertexes[1]);
	glTexCoord2f(1.0f, 0.0f);
	glVertex3fv(vertexes[2]);
	glTexCoord2f(0.0f, 0.0f);
	glVertex3fv(vertexes[3]);
	glEnd();

	// Back face
	glBindTexture(GL_TEXTURE_2D, tex[1].getId());
	glBegin(GL_QUADS);
	glTexCoord2f(0.0f, 1.0f);
	glVertex3fv(vertexes[5]);
	glTexCoord2f(1.0f, 1.0f);
	glVertex3fv(vertexes[4]);
	glTexCoord2f(1.0f, 0.0f);
	glVertex3fv(vertexes[7]);
	glTexCoord2f(0.0f, 0.0f);
	glVertex3fv(vertexes[6]);
	glEnd();

	// Top face
	glBindTexture(GL_TEXTURE_2D, tex[2].getId());
	glBegin(GL_QUADS);
	glTexCoord2f(0.0f, 1.0f);
	glVertex3fv(vertexes[4]);
	glTexCoord2f(1.0f, 1.0f);
	glVertex3fv(vertexes[5]);
	glTexCoord2f(1.0f, 0.0f);
	glVertex3fv(vertexes[1]);
	glTexCoord2f(0.0f, 0.0f);
	glVertex3fv(vertexes[0]);
	glEnd();

	// Bottom face
	glBindTexture(GL_TEXTURE_2D, tex[3].getId());
	glBegin(GL_QUADS);
	glTexCoord2f(0.0f, 1.0f);
	glVertex3fv(vertexes[3]);
	glTexCoord2f(1.0f, 1.0f);
	glVertex3fv(vertexes[2]);
	glTexCoord2f(1.0f, 0.0f);
	glVertex3fv(vertexes[6]);
	glTexCoord2f(0.0f, 0.0f);
	glVertex3fv(vertexes[7]);
	glEnd();

	// Right face
	glBindTexture(GL_TEXTURE_2D, tex[4].getId());
	glBegin(GL_QUADS);
	glTexCoord2f(0.0f, 1.0f);
	glVertex3fv(vertexes[1]);
	glTexCoord2f(1.0f, 1.0f);
	glVertex3fv(vertexes[5]);
	glTexCoord2f(1.0f, 0.0f);
	glVertex3fv(vertexes[6]);
	glTexCoord2f(0.0f, 0.0f);
	glVertex3fv(vertexes[2]);
	glEnd();

	// Left face
	glBindTexture(GL_TEXTURE_2D, tex[5].getId());
	glBegin(GL_QUADS);
	glTexCoord2f(0.0f, 1.0f);
	glVertex3fv(vertexes[4]);
	glTexCoord2f(1.0f, 1.0f);
	glVertex3fv(vertexes[0]);
	glTexCoord2f(1.0f, 0.0f);
	glVertex3fv(vertexes[3]);
	glTexCoord2f(0.0f, 0.0f);
	glVertex3fv(vertexes[7]);
	glEnd();

	glPopMatrix();
	glEnable(GL_CULL_FACE);
	glEnable(GL_LIGHTING);
	glEnable(GL_DEPTH_TEST); // Enables Depth Testing
}
