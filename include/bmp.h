#ifndef BMP_H_
#define BMP_H_

#include "stdio.h"
#include "stdlib.h"
#include "stdbool.h"
#include "string.h"
#include "stdint.h"

#pragma pack(push, 2)

static const int PIXEL_SZ = 3;

typedef struct bmp {
	uint16_t bfType;
	uint32_t bfSize;
	uint16_t bfReserved1, bfReserved2; 
	uint32_t bfOffBits;

	uint32_t biSize;
	int32_t biWidth, biHeight;
	uint16_t biPlanes, biBitCount;
	uint32_t biCompression, biSizeImage;
	int32_t biXPelsPerMeter, biYPelsPerMeter;
	uint32_t biClrUsed, biClrImportant;
	
	char* data;
} bmp_t;


int load_bmp(bmp_t* bmp, const char* file, int* x);
int save_bmp(bmp_t* bmp, const char* file);
int crop(const bmp_t *from, bmp_t* v_to, const int x, const int y, const int w, const int h);
int rotate(const bmp_t *from, bmp_t* v_to);


#endif
