#include "image-io.h"
#include <math.h>

#define MAXROW	100

#pragma once
int readImage();
void writeImage(int geladen);
void showImage();
void dilateration(unsigned char image[MAXXDIM][MAXYDIM], unsigned char image_new[MAXXDIM][MAXYDIM]);
void erodieren(unsigned char image[MAXXDIM][MAXYDIM], unsigned char image_new[MAXXDIM][MAXYDIM]);
int count_pix(unsigned char image[MAXXDIM][MAXYDIM]);
void opening(unsigned char image[MAXXDIM][MAXYDIM], unsigned char image_new[MAXXDIM][MAXYDIM], int anzahl);
void closing(unsigned char image[MAXXDIM][MAXYDIM], unsigned char image_new[MAXXDIM][MAXYDIM], int anzahl);
void mergeImage(unsigned char image1[MAXXDIM][MAXYDIM], unsigned char image2[MAXXDIM][MAXYDIM], unsigned char image_new[MAXXDIM][MAXYDIM]);
int grassfireCount(unsigned char image[MAXXDIM][MAXYDIM]);
void drawHistogram(unsigned char image[MAXXDIM][MAXYDIM], unsigned char image_new[MAXXDIM][MAXYDIM]);
void stretchingHistogram(unsigned char image[MAXXDIM][MAXYDIM], unsigned char image_new[MAXXDIM][MAXYDIM]);
void smoothingHistogram(unsigned char image[MAXXDIM][MAXYDIM], unsigned char image_new[MAXXDIM][MAXYDIM], int grayValues);

/*
typ:	1: 1. Ableitung X
		2: 1. Ableitung Y
		3: 1. Ableitung XY
		4: 2. Ableitung
*/
void derivation(unsigned char image[MAXXDIM][MAXYDIM], unsigned char image_new[MAXXDIM][MAXYDIM], unsigned int typ);

/*
typ:	1: Mittelwert 3x3
		2: Mittelwert 7x7
gewichtung: Gewichtungsfaktor für Mittelpunkt
*/
//void mittelwertfilter(unsigned char image[MAXXDIM][MAXYDIM], unsigned char image_new[MAXXDIM][MAXYDIM], unsigned int typ, unsigned int gewichtung);
void mittelwertfilter(unsigned char image[MAXXDIM][MAXYDIM], unsigned char image_new[MAXXDIM][MAXYDIM], unsigned int filtergroese, unsigned int gewichtung);

/*
typ:	1: Medianfilter 3x3
		2: Medianfilter 9x9
*/
//void medianfilter(unsigned char image[MAXXDIM][MAXYDIM], unsigned char image_new[MAXXDIM][MAXYDIM], unsigned int typ);
void medianfilter(unsigned char image[MAXXDIM][MAXYDIM], unsigned char image_new[MAXXDIM][MAXYDIM], unsigned int filtergroeße);

/**
Laws Filter
*/
void lawsfilter(unsigned char image[MAXXDIM][MAXYDIM], unsigned char image_new[MAXXDIM][MAXYDIM]);

void DoG(unsigned char image[MAXXDIM][MAXYDIM], unsigned char image_new[MAXXDIM][MAXYDIM], int scale);

void blobColoring(unsigned char image[MAXXDIM][MAXYDIM], unsigned char image_new[MAXXDIM][MAXYDIM], int toleranz);

unsigned long long CooccurrenceMatrix(unsigned char image[MAXXDIM][MAXYDIM], unsigned char image_new[MAXXDIM][MAXYDIM]);