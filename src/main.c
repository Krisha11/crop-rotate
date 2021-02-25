#include "bmp.h"
#include "stdio.h"
#include "stdlib.h"
#include "string.h"

int crop_rotate(int argc, char** argv)
{
	if (argc != 8)
		return 1;

	char* filein = argv[2];
	char* fileout = argv[3];
	int y = atoi(argv[4]), x = atoi(argv[5]), w = atoi(argv[6]), h = atoi(argv[7]);

	int flag = 0;
	bmp_t *bmp = (bmp_t*)calloc(1, sizeof(bmp_t)), *crop_bmp = (bmp_t*)calloc(1, sizeof(bmp_t)), *rotate_bmp = (bmp_t*)calloc(1, sizeof(bmp_t));

	if (bmp == NULL || crop_bmp == NULL || rotate_bmp == NULL)
		flag = 2;
	else if (load_bmp(bmp, filein, &x))
		flag = 3;
	else if (crop(bmp, crop_bmp, x, y, w, h))
		flag = 4;
	else if (rotate(crop_bmp, rotate_bmp))
		flag = 5;
	else if (save_bmp(rotate_bmp, fileout))
		flag = 6;

	if (bmp->data != NULL)
		free(bmp->data);
	if (bmp != NULL)
		free(bmp);
	if (crop_bmp->data != NULL)
		free(crop_bmp->data);
	if (crop_bmp != NULL)
		free(crop_bmp);	
	if (rotate_bmp->data != NULL)
		free(rotate_bmp->data);
	if (rotate_bmp != NULL)
		free(rotate_bmp);

	return flag;
}

int main(int argc, char** argv)
{
	if (argc <= 1)
		return -1;
	if (strcmp(argv[1], "crop-rotate") == 0)
		return crop_rotate(argc, argv);
	return 2;
}

