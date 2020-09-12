#ifndef _SHOT_H_
#define _SHOT_H_

class Bullet
{
private:
	int id;
protected:
	float x, y, z;
	float s_x, s_y, s_z;
	float vx, vy, vz;
public:
	Bullet(int id);
	int geId();
	virtual bool shoot(float angle, float x, float y, float z) = 0;
	virtual bool explode() = 0;
	virtual bool isStored() = 0;
	virtual bool inLaunch() = 0;
	virtual void render() = 0;
	virtual void move() = 0;
	virtual void reset() = 0;
};

class ExplodeEvent
{
public:
	virtual void explode(Bullet * bullet) = 0;
};

class Shot: public Bullet
{
private:
	ExplodeEvent * explode_event;
	bool stored;
	bool in_launch;
	bool exploded;
public:
	Shot(int id);
	virtual bool explode();
	virtual bool isStored();
	virtual bool inLaunch();
	virtual bool shoot(float angle, float x, float y, float z);
	virtual void render();
	virtual void move();
	virtual void reset();
	void setExplodeEvent(ExplodeEvent * explode_event);
};

#endif /* _SHOT_H_ */
