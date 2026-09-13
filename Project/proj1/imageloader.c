/************************************************************************
**
** NAME:        imageloader.c
**
** DESCRIPTION: CS61C Fall 2020 Project 1
**
** AUTHOR:      Dan Garcia  -  University of California at Berkeley
**              Copyright (C) Dan Garcia, 2020. All rights reserved.
**              Justin Yokota - Starter Code
**				Wei Xu
**
**
** DATE:        2020-08-15
**
**************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <inttypes.h>
#include <string.h>
#include "imageloader.h"

//Opens a .ppm P3 image file, and constructs an Image object. 
//You may find the function fscanf useful.
//Make sure that you close the file with fclose before returning.
Image *readData(char *filename) 
{
	FILE *fp = fopen(filename, "r");
	if (!fp) return NULL;

	Image *img = (Image *)malloc(sizeof(Image));
	if (!img) {
        fclose(fp);
        return NULL;
    }
	char format[3];
	fscanf(fp, "%2s", format);
	fscanf(fp, "%" SCNu32  " %" SCNu32, &img->cols, &img->rows);
	uint32_t scale;
	fscanf(fp, "%" SCNu32, &scale);

	img->image = (Color **)malloc(img->rows * sizeof(Color *));
	for (uint32_t i = 0; i < img->rows; i++) {
		img->image[i] = (Color *)malloc(img->cols * sizeof(Color));
		for (uint32_t j = 0; j < img->cols; j++) {
			fscanf(fp, "%" SCNu8" %" SCNu8 " %" SCNu8, 
				&img->image[i][j].R,
				&img->image[i][j].G,
				&img->image[i][j].B);
		}
	}

	fclose(fp);
	return img;
}

//Given an image, prints to stdout (e.g. with printf) a .ppm P3 file with the image's data.
void writeData(Image *image)
{
	if (!image) return;
	printf("P3\n");
    printf("%" PRIu32 " %" PRIu32 "\n", image->cols, image->rows);
    printf("255\n");
	for (uint32_t i = 0; i < image->rows; i++) {
		for (uint32_t j = 0; j < image->cols; j++) {
			printf("%3u %3u %3u", 
				image->image[i][j].R, image->image[i][j].G, image->image[i][j].B);
			if (j < image->cols - 1) printf("   ");
		}
		printf("\n");
	}
}

//Frees an image
void freeImage(Image *image)
{
	for (uint32_t i = 0; i < image->rows; i++) {
		free(image->image[i]);
	}
	free(image->image);
	free(image);
}