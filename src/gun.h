#ifndef _GUN_H_
#define _GUN_H_
#include <vector>
#include <list>
#include "shot.h"
#include "texturemanager.h"
#include "tiny_obj_loader.h"

class Gun:public ExplodeEvent
{
private:
	bool shooting;
	bool stopping;
	float velocity;
	float angle;
	float x, y, z;
	float bullet_hit;
	TextureManager* texman;
	std::vector<tinyobj::shape_t> shapes;
	std::list<Bullet*> bullets;
	std::list<Bullet*> unavalaible;
public:
	Gun(int max_shots, TextureManager* texman);
	~Gun();
	bool isShooting();
	void shoot(float angle, float x, float y, float z);
	void start();
	void stop();
	void render();
	void move();
	virtual void explode(Bullet* bullet);
};

#endif /* _GUN_H_ */
