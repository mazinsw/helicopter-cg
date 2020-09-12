#include "shot.h"
#include "util.h"
#include <math.h>
#include <GL/gl.h>
#include <stdio.h>

Shot::Shot(int id): Bullet(id)
{
	stored = true;
	exploded = false;
	in_launch = false;
	this->explode_event = NULL;
}

bool Shot::explode()
{
	if(inLaunch() && !isStored())
	{
		if(sqrt(pow(x - s_x, 2) + pow(y - s_y, 2) + pow(z - s_z, 2)) < 10)
			return false;
		in_launch = false;
		exploded = true;
		if(explode_event != NULL)
			explode_event->explode(this);
		return true;
	}
	return false;
}

bool Shot::isStored()
{
	return stored;
}

bool Shot::inLaunch()
{
	return in_launch;
}

bool Shot::shoot(float angle, float x, float y, float z)
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
		vx = 1.0f;//sin(2 * M_PI * y_angle / 360);
		stored = false;
		in_launch = true;
		return true;
	}
	return false;
}

void Shot::render()
{
	if(exploded || !in_launch)
		return;
	glPushMatrix();
	glRotatef(-90.0f, 0.0f, 1.0f, 0.0f);
	glTranslatef(-x, 0, -z);
	glTranslatef(s_x, 0.0f, 0.0f);
	glScalef(0.05f, 0.05f, 0.05f);
	drawCube();
	glPopMatrix();
}

void Shot::move()
{
	if(!inLaunch())
		return;
	x += vx * 0.5;
	y += vy * 0.5;
	z += vz * 0.5;
	if(sqrt(pow(x - s_x, 2) + pow(y - s_y, 2) + pow(z - s_z, 2)) > 100)
		explode();
}

void Shot::setExplodeEvent(ExplodeEvent* explode_event)
{
	this->explode_event = explode_event;
}

void Shot::reset()
{
	stored = true;
	exploded = false;
	in_launch = false;
}


Bullet::Bullet(int id)
{
	this->id = id;
	x = y = z = 0.0f;
	s_x = s_y = s_z = 0.0f;
	vx = vy = vz = 0.0f;
}

int Bullet::geId()
{
	return id;
}

