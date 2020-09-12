#include <GL/gl.h>
#include "rotor.h"
#include "objloader.h"
#define ACCELERATION 0.1f
#define LIMIT_ROTOR 30.0f

Rotor::Rotor(TextureManager* texman)
{
	this->texman = texman;
	load_object("../res/main_rotor.obj", "../res/", shapes, texman);
	is_rotate = false;
	stopping = false;
	velocity = 0.0f;
	angle = 0.0f;
}

void Rotor::rotate()
{
	if(!is_rotate)
		stopping = false;
	is_rotate = true;
	if(stopping)
	{
		if(velocity > 0)
			velocity -= ACCELERATION;
		angle += velocity;
		if(velocity <= 0)
		{
			is_rotate = false;
			stopping = false;
		}
	}
	else
	{
		if(velocity < LIMIT_ROTOR)
			velocity += ACCELERATION;
		angle += velocity;
	}
}

void Rotor::stop()
{
	stopping = true;
}

bool Rotor::isRotate()
{
	return is_rotate;
}

void Rotor::render()
{
	glPushMatrix();
	glRotatef(angle, 0.0f, 1.0f, 0.0f);
	render_object(shapes, texman);
	glPopMatrix();
}

bool Rotor::isDone()
{
	return velocity >= LIMIT_ROTOR && is_rotate;
}

float Rotor::getAngle()
{
	return angle;
}



