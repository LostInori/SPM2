#include <stdio.h>
//#include "image-io.h"
#include "funktionen.h"

unsigned char image[MAXXDIM][MAXYDIM];

void emptyImage(unsigned char image[MAXXDIM][MAXYDIM])
{
	for (int x = 0; x < MAXXDIM; x++)
		for (int y = 0; y < MAXYDIM; y++)
			image[x][y] = 0;
}

void cpyImage(unsigned char original[MAXXDIM][MAXYDIM], unsigned char kopie[MAXXDIM][MAXYDIM])
{
	for (int x = 0; x < MAXXDIM; x++)
		for (int y = 0; y < MAXYDIM; y++)
			kopie[x][y] = original[x][y];
}

void showImage()
{
	viewImage_ppm();
}

int readImage()
{
	int rueckgabe = 1;
	if (readImage_ppm(image) == 0) //Erfolgreich geladen
	{
		rueckgabe = 0;
	}
	else
	{
		rueckgabe = 1;
		printf("Es ist ein Fehler beim Laden aufgetreten.");
		getchar();
	}
	return rueckgabe; //Rückgabe 1 = Fehler; 0 = Alles OK
}

void writeImage(int geladen)
{
	if (!geladen)
	{
		if (writeImage_ppm(image, MAXXDIM, MAXYDIM) > 0)
		{
			//Fehlermeldung
			printf("Es ist ein Fehler aufgetreten");
			getchar();
		}
	}
	else
	{
		printf("Es wurde keine Datei geladen, die gespeichert werden konnte");
		getchar();
	}

}

void dilateration(unsigned char image[MAXXDIM][MAXYDIM], unsigned char image_new[MAXXDIM][MAXYDIM])
{
	emptyImage(image_new);

	for (int x = 0; x < MAXXDIM; x++)
	{
		for (int y = 0; y < MAXYDIM; y++)
		{
			if (image[x][y] == 255)
			{
				image_new[x][y] = 255;
				image_new[x][y-1] = 255;
				image_new[x][y+1] = 255;
				image_new[x-1] [y] = 255;
				image_new[x+1][y] = 255;
			}
		}
	}
}

void erodieren(unsigned char image[MAXXDIM][MAXYDIM], unsigned char image_new[MAXXDIM][MAXYDIM])
{
	emptyImage(image_new);
	for (int x = 0; x < MAXXDIM; x++)
	{
		for (int y = 0; y < MAXYDIM; y++)
		{
			if (image[x][y] == 255 &&
				image[x][y-1] == 255 && 
				image[x][y+1] == 255 && 
				image[x-1][y] == 255 &&
				image[x+1][y] == 255)
			{ 
				image_new[x][y] = image[x][y];
			}
		}
	}
}

int count_pix(unsigned char image[MAXXDIM][MAXYDIM])
{
	int counter = 0;
	for (int x = 0; x < MAXXDIM; x++)
	{
		for (int y = 0; y < MAXYDIM; y++)
		{
			if (image[x][y] != 0)
			{
				counter++;
			}
		}
	}
	return counter;
}

void invertImage(unsigned char image[MAXXDIM][MAXYDIM], unsigned char image_new[MAXXDIM][MAXYDIM])
{
	emptyImage(image_new);
	for (int x = 0; x < MAXXDIM; x++)
		for (int y = 0; y < MAXXDIM; y++)
			if (image[x][y] != 0)
				image_new[x][y] = 0;
			else
				image_new[x][y] = 255;
}

void mergeImage(unsigned char image1[MAXXDIM][MAXYDIM], unsigned char image2[MAXXDIM][MAXYDIM], unsigned char image_new[MAXXDIM][MAXYDIM])
{
	emptyImage(image_new);
	for (int x = 0; x < MAXXDIM; x++)
		for (int y = 0; y < MAXYDIM; y++)
		{
			if (image1[x][y] == image2[x][y])
			{
				if (image1[x][y] == 0)
					image_new[x][y] == 0;
				if (image1[x][y] == 255)
					image_new[x][y] == 255;
			}
		}
}

void opening(unsigned char image[MAXXDIM][MAXYDIM], unsigned char image_new[MAXXDIM][MAXYDIM], int anzahl)
{
	unsigned char imageCopy[MAXXDIM][MAXYDIM];
	unsigned char image2[MAXXDIM][MAXYDIM];
	unsigned char image3[MAXXDIM][MAXYDIM];
//	int k = 0;


	emptyImage(image_new);
	emptyImage(image2);
	emptyImage(image3);
	cpyImage(image, imageCopy);

	for (int i = 0; i < anzahl; i++)
	{
		erodieren(imageCopy, image2);
		cpyImage(image2, imageCopy);
	}

	for (int i = 0; i < anzahl; i++)
	{
		dilateration(imageCopy, image3);
		cpyImage(image3, imageCopy);
	}
	cpyImage(image3, image_new);
}

void closing(unsigned char image[MAXXDIM][MAXYDIM], unsigned char image_new[MAXXDIM][MAXYDIM], int anzahl)
{
	unsigned char imageCopy[MAXXDIM][MAXYDIM];
	unsigned char image2[MAXXDIM][MAXYDIM];
	unsigned char image3[MAXXDIM][MAXYDIM];
	int k = 0;


	emptyImage(image_new);
	emptyImage(image2);
	emptyImage(image3);
	cpyImage(image, imageCopy);

	for (int i = 0; i < anzahl; i++)
	{
		dilateration(imageCopy, image2);
		cpyImage(image2, imageCopy);
	}

	for (int i = 0; i < anzahl; i++)
	{
		erodieren(imageCopy, image3);
		cpyImage(image3, imageCopy);
	}
	cpyImage(image3, image_new);

}

void dilateCircleOnPoint(unsigned char image[MAXXDIM][MAXYDIM], int posX, int posY)
{
	image[posX][posY] = 255;
	image[posX][posY+1] = 255;
	image[posX+1][posY+1] = 255;
	image[posX][posY-1] = 255;
	image[posX-1][posY-1] = 255;
	image[posX-1][posY+1] = 255;
	image[posX+1][posY-1] = 255;
	image[posX-1][posY] = 255;
	image[posX][posY+1] = 255;
}

int grassfireCount(unsigned char image[MAXXDIM][MAXYDIM])
{
	unsigned char imageCopy[MAXXDIM][MAXYDIM];
	unsigned char image1[MAXXDIM][MAXYDIM];
	unsigned char image2[MAXXDIM][MAXYDIM];
	int counter = 0;
	int counter1 = 0;

	emptyImage(image1);
	emptyImage(image2);
	emptyImage(imageCopy);
	cpyImage(image, imageCopy);
	

	for (int x = 0; x < MAXXDIM; x++)
	{
		for (int y = 0; y < MAXYDIM; y++)
		{
			if (imageCopy[x][y] == 0)
			{
				dilateCircleOnPoint(image1, x, y);
				for (int i = 0; i < MAXXDIM; i++)
					for (int j = 0; j < MAXYDIM; j++)
					{
						if (count_pix(image1) != counter1)
						{
							counter1 = count_pix(image1);
							image2[i][j] = imageCopy && image1;
							dilateCircleOnPoint(image1, i + 1, j);
						}
						else
							counter++;
					}
						
			}
		}
	}

	return counter;
}