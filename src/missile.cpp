#include <GL/gl.h>
#include <math.h>
#include <stdio.h>
#include "missile.h"
#include "objloader.h"

Missile::Missile(TextureManager* texman, std::string obj, int id): Bullet(id)
{
	this->texman = texman;
	load_object(obj, "../res/", shapes, texman);
	stored = true;
	in_launch = false;
	exploded = false;
	explode_event = NULL;
}

bool Missile::shoot(float angle, float x, float y, float z)
{
	if(isStored() && !inLaunch())
	{
		this->x = x;
		this->y = y;
		this->z = z;
		s_x = x;
		s_y = y;
		s_z = z;
		vy = 0;
		float y_angle = angle + 90.0f;
		if(y_angle < 0.0f)
			y_angle = -y_angle - 360.0f;
		vz = 0.0f;//cos(2 * M_PI * y_angle / 360);
		vx = 1.0;//sin(2 * M_PI * y_angle / 360);
		stored = false;
		in_launch = true;
		return true;
	}
	return false;
}

bool Missile::explode()
{
	if(inLaunch() && !isStored())
	{
		if(sqrt(pow(x - s_x, 2) + pow(y - s_y, 2) + pow(z - s_z, 2)) < 10)
			return false;
		if(explode_event != NULL)
			explode_event->explode(this);
		in_launch = false;
		exploded = true;
		return true;
	}
	return false;
}

bool Missile::isStored()
{
	return stored;
}

bool Missile::inLaunch()
{
	return in_launch;
}

void Missile::render()
{
	if(exploded)
		return;
	glPushMatrix();
	glRotatef(-90.0f, 0.0f, 1.0f, 0.0f);
	glTranslatef(-x, 0, z);
	glRotatef(90.0f, 0.0f, 1.0f, 0.0f);
	glTranslatef(s_x, 0.0f, 0.0f);
	render_object(shapes, texman);
	glPopMatrix();
}

void Missile::move()
{
	if(!inLaunch())
		return;
	x += vx * 0.1;
	y += vy * 0.1;
	z += vz * 0.1;
	if(sqrt(pow(x - s_x, 2) + pow(y - s_y, 2) + pow(z - s_z, 2)) > 100)
		explode();
}

void Missile::setExplodeEvent(ExplodeEvent* explode_event)
{
	this->explode_event = explode_event;
}

void Missile::reset()
{
	stored = true;
	in_launch = false;
	exploded = false;
}
