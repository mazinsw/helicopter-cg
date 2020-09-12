#ifndef __IMAGE_H__
#define __IMAGE_H__

typedef struct
{
	unsigned short imagic;
	unsigned short type;
	unsigned short dim;
	unsigned short sizeX, sizeY, sizeZ;
	char name[128];
	unsigned char *data;
} IMAGE;

IMAGE *ImageLoad(const char * filename);

void ImageFree(IMAGE * image);

#endif /* !__IMAGE_H__! */
