#ifndef _SCENERY_H_
#define _SCENERY_H_
#include "texture.h"

class Scenery
{
private:
	unsigned int gl_list;
	Texture tex;
	void makeList();
protected:
	
public:
	void load();
	void render();
};

#endif /* _SCENERY_H_ */