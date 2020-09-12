#ifndef _PLAYER_H_
#define _PLAYER_H_
#include "camera.h"
#include "keyaction.h"

class Player
{
private:
	float x_trans, y_trans, z_trans;
	int curr_x_dir, curr_z_dir;
	float acceleration, velocity_limit, velocity, breaking_accel;
	float velocity_x, velocity_z;
	bool constant_velocity;
	KeyAction x_action;
public:
	Player();

	inline float getXDist()
	{
		return x_trans;
	}

	inline float getYDist()
	{
		return y_trans;
	}

	inline float getZDist()
	{
		return z_trans;
	}

	inline void setXDist(float dx)
	{
		x_trans = dx;
	}

	inline void setYDist(float dy)
	{
		y_trans = dy;
	}

	inline void setZDist(float dz)
	{
		z_trans = dz;
	}

	inline void setAcceleration(float accel)
	{
		acceleration = accel;
	}

	inline void setBreakingAcceleration(float break_accel)
	{
		breaking_accel = break_accel;
	}

	inline void setVelocity(float vel)
	{
		velocity = vel;
	}

	inline void setVelocityLimit(float limit)
	{
		velocity_limit = limit;
	}

	inline void setConstantVelocity(bool constant)
	{
		constant_velocity = constant;
	}

	inline float getAcceleration()
	{
		return acceleration;
	}

	inline float getBreakingAcceleration()
	{
		return breaking_accel;
	}

	inline float getVelocity()
	{
		return velocity;
	}

	inline float getVelocityLimit()
	{
		return velocity_limit;
	}

	inline bool isConstantVelocity()
	{
		return constant_velocity;
	}

	inline KeyAction& getXAction()
	{
		return x_action;
	}
	
	virtual float getYAngle()
	{
		return 0.0f;
	}

	virtual void update(int key, bool down)
	{
		x_action.update(key, down);
		if(x_action.getSide() != curr_x_dir && x_action.inAction())
			curr_x_dir = x_action.getSide();
	}

	virtual void move();
};
#endif

