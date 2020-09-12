#ifndef _HELICOPTER_H_
#define _HELICOPTER_H_
#include <vector>
#include "missile.h"
#include "gun.h"
#include "rotor.h"
#include "tail_rotor.h"
#include "tiny_obj_loader.h"
#include "texturemanager.h"
#include "player.h"
#include "sound.h"
#include "shot.h"

class Helicopter: public Player, ExplodeEvent
{
private:
	Sound shootStart, shootEnd;
	Sound rotorStart;
	Sound soundMissile;
	TextureManager* texman;
	Missile * missile_left;
	Missile * missile_right;
	Rotor * rotor;
	TailRotor * tail_rotor;
	Gun * gun;
	int max_shots;
	std::vector<tinyobj::shape_t> shapes;
	KeyAction updown_action;
	KeyAction z_action;
	float y_angle;
	float velocity;
	float acceleration;
public:
	Helicopter(int max_shots, TextureManager* texman);
	~Helicopter();
	void render();
	bool shootMissileLeft();
	bool shootMissileRight();
	void startShootGun();
	void stopShootGun();
	virtual void explode(Bullet * bullet);

	virtual float getYAngle()
	{
		return y_angle;
	}

	inline KeyAction& getUpDownAction()
	{
		return updown_action;
	}
	
	inline KeyAction& getZAction()
	{
		return z_action;
	}

	virtual void update(int key, bool down)
	{
		Player::update(key, down);
		updown_action.update(key, down);
		z_action.update(key, down);
		if(updown_action.inAction() && updown_action.getSide() == 1 && !rotor->isRotate())
		{
			rotor->rotate();
			rotorStart.play();
		}
	}

	virtual void move();
};

#endif /* _HELICOPTER_H_ */
