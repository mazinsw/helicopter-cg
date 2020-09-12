#include <GL/gl.h>
#include "gun.h"
#include "objloader.h"
#define ACCELERATION_GUN 2.0f
#define BREAKING_GUN 0.5f
#define LIMIT_GUN 18.0f
#include <stdio.h>

Gun::Gun(int max_shots, TextureManager* texman)
{
	this->texman = texman;
	load_object("../res/gun.obj", "../res/", shapes, texman);
	shooting = false;
	stopping = false;
	velocity = 0.0f;
	angle = 0.0f;
	bullet_hit = 0.0f;
	for(int i = 0; i < max_shots; i++)
	{
		Shot * bullet = new Shot(i + 3);
		bullet->setExplodeEvent(this);
		bullets.push_back(bullet);
	}
}

Gun::~Gun()
{
	for(std::list<Bullet*>::iterator it = bullets.begin(); it != bullets.end(); it++)
		delete *it;
	for(std::list<Bullet*>::iterator it = unavalaible.begin(); it != unavalaible.end(); it++)
		delete *it;
}

void Gun::shoot(float angle, float x, float y, float z)
{
	if(stopping)
	{
		if(velocity > 0)
			velocity -= BREAKING_GUN;
		this->angle += velocity;
		if(velocity <= 0)
		{
			shooting = false;
			stopping = false;
		}
	}
	else
	{
		if(velocity < LIMIT_GUN)
			velocity += ACCELERATION_GUN;
		this->angle += velocity;
		bullet_hit += velocity;
		if(this->angle > 360)
			this->angle -= 360;
		if(bullet_hit > 100)
		{
			bullet_hit = 0;
			if(!bullets.empty())
			{
				Bullet * bullet = bullets.back();
				bullets.pop_back();
				unavalaible.push_back(bullet);
				bullet->shoot(angle, x, y, z);
			}
		}
	}
}

void Gun::render()
{
	glPushMatrix();
	for(std::list<Bullet*>::iterator it = unavalaible.begin(); it != unavalaible.end(); it++)
		(*it)->render();
	glTranslatef(0.000012, -0.145312, -0.545853);
	glRotatef(-90.0f, 0.0f, 0.0f, 1.0f);
	glRotatef(angle, 0.0f, 0.0f, 1.0f);
	glRotatef(90.0f, 0.0f, 0.0f, 1.0f);
	glTranslatef(-0.000012, 0.145312, 0.545853);
	render_object(shapes, texman);
	glPopMatrix();
}

void Gun::start()
{
	stopping = false;
	shooting = true;
}

bool Gun::isShooting()
{
	return shooting;
}

void Gun::stop()
{
	stopping = true;
}

void Gun::move()
{
	std::list<Bullet*>::iterator prox;
	for(std::list<Bullet*>::iterator it = unavalaible.begin(); it != unavalaible.end();)
	{
		prox = it;
		prox++;
		Bullet* bullet = *it;
		bullet->move();
		if(!bullet->inLaunch())
		{
			it = prox;
			continue;
		}
		it++;
	}
}

void Gun::explode(Bullet* bullet)
{
	for(std::list<Bullet*>::iterator it = unavalaible.begin(); it != unavalaible.end(); it++)
	{
		if(*it == bullet)
		{
			bullets.push_front(bullet);
			bullet->reset();
			unavalaible.erase(it);
			break;
		}
	}
}
