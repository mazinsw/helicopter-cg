#ifndef _CAMERA_H_
#define _CAMERA_H_

class Camera
{
private:
	float rot_y, rot_x, rot_z;
	float x, y, z;
public:
	Camera();

	inline float getXAngle()
	{
		return rot_x;
	}

	inline float getYAngle()
	{
		return rot_y;
	}

	inline float getZAngle()
	{
		return rot_z;
	}

	inline void setXAngle(float ax)
	{
		rot_x = ax;
	}

	inline void setYAngle(float ay)
	{
		rot_y = ay;
	}

	inline void setZAngle(float az)
	{
		rot_z = az;
	}
	
	inline void setXYZ(float x, float y, float z)
	{
		this->x = x;
		this->y = y;
		this->z = z;
	}
		
	inline float getX()
	{
		return x;
	}
	
	inline float getY()
	{
		return y;
	}
	
	inline float getZ()
	{
		return z;
	}

	void look();
	void move();
};
#endif

