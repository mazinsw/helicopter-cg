#ifndef _MISSILE_H_
#define _MISSILE_H_
#include <vector>
#include "texturemanager.h"
#include "tiny_obj_loader.h"
#include "shot.h"

class Missile: public Bullet
{
private:
	bool stored;
	bool in_launch;
	bool exploded;
	TextureManager* texman;
	std::vector<tinyobj::shape_t> shapes;
	ExplodeEvent * explode_event;
public:
	Missile(TextureManager* texman, std::string obj, int id);
	void setExplodeEvent(ExplodeEvent * explode_event);
	virtual bool explode();
	virtual bool isStored();
	virtual bool inLaunch();
	virtual bool shoot(float angle, float x, float y, float z);
	virtual void render();
	virtual void move();
	virtual void reset();
};

#endif /* _MISSILE_H_ */
