#ifndef _ROTOR_H_
#define _ROTOR_H_
#include <vector>
#include "texturemanager.h"
#include "tiny_obj_loader.h"

class Rotor
{
private:
	bool is_rotate;
	bool stopping;
	TextureManager* texman;
	std::vector<tinyobj::shape_t> shapes;
	float velocity;
	float angle;
public:
	Rotor(TextureManager* texman);
	void rotate();
	void stop();
	bool isRotate();
	bool isDone();
	void render();
	float getAngle();
};


#endif /* _ROTOR_H_ */
