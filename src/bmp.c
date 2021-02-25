#include "bmp.h"
#include "stdio.h"

static size_t get_real_w(const size_t w)
{
	int to = 4;
	if (w % to == 0)
		return w;
	return w + (to - w % to);
}

int load_bmp(bmp_t *bmp, const char *file, int *x)
{
	FILE* f = fopen(file, "rb");
	if (f == NULL)
		return 1;
	fread(bmp, sizeof(bmp_t) - sizeof(char*), 1, f);
	fseek(f, bmp->bfOffBits, 0);
	bmp->data = (char*)calloc(bmp->bfSize - bmp->bfOffBits, 1);
	if (bmp->data == NULL)
		return false;	
	fread(bmp->data, bmp->bfSize - bmp->bfOffBits, 1, f);
	fclose(f);

	*x = bmp->biHeight - 1 - *x;
	return 0;
}

int crop(const bmp_t *from, bmp_t* v_to, const int x, const int y, const int w, const int h)
{
	if (x >= from->biHeight || y + w - 1 >= from->biWidth || x - h + 1 < 0 || y < 0)
		return 1;

	v_to = memcpy(v_to, from, sizeof(bmp_t));
	if (v_to == NULL)
		return 2;	
	v_to->data = (char*)calloc(get_real_w(w * PIXEL_SZ) * h, 1);
	if (v_to->data == NULL)
		return 3;

	v_to->biWidth = w;
	v_to->biHeight = h;
	v_to->bfSize += (get_real_w(v_to->biWidth * PIXEL_SZ)) * (v_to->biHeight) - (get_real_w(from->biWidth * PIXEL_SZ)) * (from->biHeight);
	v_to->biSizeImage = get_real_w(v_to->biWidth * PIXEL_SZ) * (v_to->biHeight);
	for (int i = x - h + 1; i <= x; i++)
		for (int j = y; j < y + w; j++)
			for (int q = 0; q < PIXEL_SZ; q++)
				v_to->data[((i - (x - h + 1)) * get_real_w(v_to->biWidth * PIXEL_SZ) + (j - y) * PIXEL_SZ) + q] = from->data[(i * get_real_w(from->biWidth * PIXEL_SZ) + j * PIXEL_SZ) + q];

	return 0;
}


int rotate(const bmp_t *from, bmp_t* v_to)
{
	v_to = memcpy(v_to, from, sizeof(bmp_t));
	if (v_to == NULL)
		return 1;	
	v_to->data = (char*)calloc(get_real_w(v_to->biHeight) * v_to->biWidth * PIXEL_SZ, 1);
	if (v_to->data == NULL)
		return 2;
	
	for (int i = 0; i < v_to->biHeight; i++)
		for (int j = 0; j < v_to->biWidth; j++)
			for (int q = 0; q < PIXEL_SZ; q++)
				v_to->data[(v_to->biWidth - 1 - j) * get_real_w(v_to->biHeight * PIXEL_SZ) + i * PIXEL_SZ + q] = from->data[i * get_real_w(v_to->biWidth * PIXEL_SZ) + j * PIXEL_SZ + q];


	int32_t tmp = v_to->biHeight;	
	v_to->biHeight = v_to->biWidth;
	v_to->biWidth = tmp;
	v_to->bfSize += (get_real_w(v_to->biWidth * PIXEL_SZ)) * (v_to->biHeight) - (get_real_w(from->biWidth * PIXEL_SZ)) * (from->biHeight);
	v_to->biSizeImage = get_real_w(v_to->biWidth * PIXEL_SZ) * (v_to->biHeight);

	return 0;
}

int save_bmp(bmp_t* bmp, const char* file)
{
	FILE* f = fopen(file, "wb");
	if (f == NULL)
		return 1;

	if (fwrite(bmp, sizeof(bmp_t) - sizeof(char*), 1, f) != 1)
		return 2;

	if (fwrite(bmp->data, bmp->bfSize - bmp->bfOffBits, 1, f) != 1)
		return 3;


	fclose(f);
	return 0;
}

