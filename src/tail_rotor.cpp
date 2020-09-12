#include <GL/gl.h>
#include "tail_rotor.h"
#include "objloader.h"

TailRotor::TailRotor(TextureManager* texman)
{
	this->texman = texman;
	load_object("../res/rear_rotor.obj", "../res/", shapes, texman);
	is_rotate = false;
	angle = 0.0f;
}

bool TailRotor::rotate()
{
	if(is_rotate == false)
	{
		is_rotate = true;
		return true;
	}
	return false;
}

bool TailRotor::stop()
{
	if(is_rotate == false)
		return false;
	is_rotate = false;
	return true;
}

bool TailRotor::isRotate()
{
	return is_rotate;
}

void TailRotor::render()
{
	glPushMatrix();
	glTranslatef(0.0351305f, 0.231942f, 1.042441f);
	glRotatef(angle, 1.0f, 0.0f, 0.0f);
	glRotatef(-7.0f, 0.0f, 1.0f, 0.0f);
	glRotatef(-90.0f, 1.0f, 0.0f, 0.0f);
	glTranslatef(-0.0351305f, -0.231942f, -1.042441f);
	render_object(shapes, texman);
	glPopMatrix();
}

void TailRotor::setAngle(float angle)
{
	this->angle = angle;
}


