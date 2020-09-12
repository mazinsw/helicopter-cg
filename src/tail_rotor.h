#ifndef _TAIL_ROTOR_H_
#define _TAIL_ROTOR_H_
#include <vector>
#include "texturemanager.h"
#include "tiny_obj_loader.h"

class TailRotor
{
private:
	bool is_rotate;
	TextureManager* texman;
	std::vector<tinyobj::shape_t> shapes;
	float angle;
public:
	TailRotor(TextureManager* texman);
	bool rotate();
	bool stop();
	bool isRotate();
	void render();
	void setAngle(float angle);
};

#endif /* _TAIL_ROTOR_H_ */
