#include "texture.h"
#include "image.h"
#include <GL/gl.h>
#include <GL/glu.h>

Texture::Texture()
{
	tex_id = 0;
}

void Texture::load(std::string file, bool mipmap)
{
	IMAGE* img = ImageLoad(file.c_str());
	glGenTextures(1, &tex_id);

	glBindTexture(GL_TEXTURE_2D, tex_id);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	if(mipmap)
	{
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_NEAREST);
		gluBuild2DMipmaps(GL_TEXTURE_2D, 3, img->sizeX, img->sizeY, GL_RGB, 
			GL_UNSIGNED_BYTE, (GLvoid*)img->data);
	}
	else
	{
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexImage2D(GL_TEXTURE_2D, 0, 3, img->sizeX, img->sizeY, 0, GL_RGB, 
			GL_UNSIGNED_BYTE, (GLvoid*)img->data);
	}
	ImageFree(img);
}
