#include "helicopter.h"
#include "util.h"
#include <string>
#include <iostream>
#include <stdlib.h>
#include <GL/gl.h>
#include "objloader.h"
#include "keyaction.h"

Helicopter::Helicopter(int max_shots, TextureManager* texman)
{
	this->texman = texman;
	this->max_shots = max_shots;
	y_angle = 0.0f;
	load_object("../res/fuselage.obj", "../res/", shapes, texman);
	shootStart.load("../res/gatling.wav");
	shootStart.setLoop(shootStart.getLength() / 2);
	shootEnd.load("../res/gatling end.wav");
	rotorStart.load("../res/rotor.wav");
	rotorStart.setLoop(2 * rotorStart.getLength() / 3.0f);
	soundMissile.load("../res/missile.wav");
	missile_left = new Missile(texman, "../res/missile_L.obj", 1);
	missile_left->setExplodeEvent(this);
	missile_right = new Missile(texman, "../res/missile_R.obj", 2);
	missile_right->setExplodeEvent(this);
	rotor = new Rotor(texman);
	tail_rotor = new TailRotor(texman);
	gun = new Gun(max_shots, texman);
	velocity = 0.0f;
	acceleration = 0.004f;
}

Helicopter::~Helicopter()
{
	delete gun;
	delete tail_rotor;
	delete rotor;
	delete missile_left;
	delete missile_right;
}

void Helicopter::render()
{
	glPushMatrix();
	glTranslatef(0.0f, getYDist(), 0.0f);
	glRotatef(-90, 0.0f, 1.0f, 0.0f);
	render_object(shapes, texman);
	rotor->render();
	tail_rotor->render();
	missile_left->render();
	missile_right->render();
	gun->render();
	glPopMatrix();
}

bool Helicopter::shootMissileLeft()
{
	if(!(rotor->isDone() && getYDist() > 0.01f))
		return false;
	if(missile_left->inLaunch())
		return missile_left->explode();
	return missile_left->shoot(getYAngle(), getXDist(), getYDist(), getZDist());
}

bool Helicopter::shootMissileRight()
{
	if(!(rotor->isDone() && getYDist() > 0.01f))
		return false;
	if(missile_right->inLaunch())
		return missile_right->explode();
	return missile_right->shoot(getYAngle(), getXDist(), getYDist(), getZDist());
}

void Helicopter::move()
{
	Player::move();
	if(updown_action.inAction())
	{
		if(rotor->isDone())
		{
			if(velocity < 0.01f)
				velocity += acceleration;
			if(getYDist() >= 0)
				setYDist(getYDist() + updown_action.getSide() * velocity);
			else
				setYDist(0);
		}
		if(updown_action.getSide() == -1 && (velocity <= 0 || getYDist() == 0) &&
				rotor->isRotate())
		{
			rotor->stop();
			rotorStart.stop();
		}
	}
	else
	{
		if(velocity - acceleration >= 0)
		{
			velocity -= acceleration;
			setYDist(getYDist() + updown_action.getSide() * velocity);
		}
	}
	if(rotor->isRotate())
	{
		rotor->rotate();
		tail_rotor->setAngle(rotor->getAngle());
	}
	if(gun->isShooting())
		gun->shoot(getYAngle(), getXDist(), getYDist(), getZDist());
	gun->move();
	if(z_action.inAction() && rotor->isDone() && getYDist() > 0.01f)
	{
		y_angle += z_action.getSide() * 1.0;
	}
	missile_left->move();
	missile_right->move();
}

void Helicopter::startShootGun()
{
	shootStart.play();
	gun->start();
}

void Helicopter::stopShootGun()
{
	shootEnd.play(1);
	shootStart.stop();
	gun->stop();
}

void Helicopter::explode(Bullet * bullet)
{
	soundMissile.play(1);
}
