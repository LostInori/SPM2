#include <stdio.h>
//#include "image-io.h"
#include "funktionen.h"

unsigned char image[MAXXDIM][MAXYDIM];

void set_image(unsigned char image[MAXXDIM][MAXYDIM], unsigned int value)
{
	for (int x = 0; x < MAXXDIM; x++)
		for (int y = 0; y < MAXXDIM; y++)
			image[x][y] = value;
}

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

void bubbleSort(int *eingangswerte, int length)
{
	int tmp = 0;

	for (int i = 1; i < length; i++)
		for (int j = 0; j < length - i; j++)
		{
			if (eingangswerte[j] > eingangswerte[j + 1])
			{
				tmp = eingangswerte[j];
				eingangswerte[j] = eingangswerte[j + 1];
				eingangswerte[j + 1] = tmp;
			}
		}
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
	if (posY < MAXYDIM) { image[posX][posY + 1] = 255; }
	if (posY - 1 < 0) { image[posX][posY - 1] = 255; }
	//if (posX > 0)
	//{
/*		image[posX - 1][posY] = 255;
		image[posX - 1][posY - 1] = 255;
		image[posX - 1][posY + 1] = 255;
	//}
	//if (posX + 1 <= MAXXDIM)
	//{
		image[posX + 1][posY] = 255;
		image[posX + 1][posY - 1] = 255;
		image[posX + 1][posY + 1] = 255;
	//}*/
	
}

void addElementarRaute(unsigned char image[MAXXDIM][MAXYDIM], int posX, int posY)
{
	image[posX][posY] = 255;
	image[posX + 1][posY] = 255;
	image[posX][posY + 1] = 255;
	image[posX][posY - 1] = 255;
	image[posX - 1][posY] = 255;
}

int grassfireCount(unsigned char image[MAXXDIM][MAXYDIM])
{
	int counterObject = 0;
	int bit = 0;
	int bit2 = 0;
	unsigned char image2[MAXXDIM][MAXYDIM];
	unsigned char image3[MAXXDIM][MAXYDIM];
	unsigned char image4[MAXXDIM][MAXYDIM];
	emptyImage(image2);
	emptyImage(image3);
	emptyImage(image4);
	

	for (int x = 0; x < MAXXDIM; x++) {
		for (int y = 0; y < MAXYDIM; y++) {
			if (image[x][y] == 255 && image4[x][y] == 0) {
				image3[x][y] = 255;	
				do {
					bit2 = bit;
					bit = 0;
					emptyImage(image2);
					for (int i = 0; i < MAXXDIM; i++)
						for (int j = 0; j < MAXYDIM; j++)
							if (image3[i][j] == 255)
								addElementarRaute(image2, i, j);

					for (int d = 0; d < MAXXDIM; d++) {
						for (int e = 0; e < MAXXDIM; e++) {
							if (image2[d][e] == 255 && image[d][e] == 255) {
								image3[d][e] = 255;
								bit++;
							}
							else {
								image3[d][e] = 0;
							}
						}
					}
					cpyImage(image3, image4);
				} while (bit != bit2);
				counterObject++;
			}
		}
	}
	return counterObject;
}

void fkt_histogram(unsigned char image[MAXXDIM][MAXYDIM], unsigned int histogram[256])
{
	for (int i = 0; i < 256; i++)
		histogram[i] = 0;

	for (int x = 0; x < MAXXDIM; x++)
		for (int y = 0; y < MAXYDIM; y++)
			histogram[image[x][y]]++;
}

void drawHistogram(unsigned char image[MAXXDIM][MAXYDIM], unsigned char image_new[MAXXDIM][MAXYDIM])
{
	unsigned int histogram[256];
	int highestValue = 0;

	emptyImage(image_new);
	fkt_histogram(image, histogram);

	//Maximalwert an Pixeln ermitteln
	for (int i = 0; i < 256; i++)
		if (histogram[i] > highestValue)
			highestValue = histogram[i];

	//Normieren der Menge an Punkten
	for (int i = 0; i < 256; i++)
		histogram[i] = (int)(((float)histogram[i] * 256.0) / (float)highestValue);

	//Bild zeichnen
	for (int y = 0; y < 256; y++)
		for (int x = 255; x > (255-histogram[y]); x--)
			image_new[x][y] = 255;
}

void stretchingHistogram(unsigned char image[MAXXDIM][MAXYDIM], unsigned char image_new[MAXXDIM][MAXYDIM])
{
	unsigned int histogram[256];
	//int counter = 0;
	int highestValue = 0;
	int maxValue = 0;
	int minValue = 0;
	int k = 0;
	int lowestValue = 255;
	fkt_histogram(image, histogram);
	emptyImage(image_new);

	for (int i = 0; i < 256; i++)
	{
		if (histogram[i] > highestValue)
			highestValue = histogram[i];
		if ((histogram[i] < lowestValue) && (histogram[i] != 0) && (lowestValue == 255))
			lowestValue = histogram[i];
	}

	for (int i = 0; i < 256; i++)
	{
		if (histogram[i] == highestValue)
			maxValue = i;
		if (histogram[i] == lowestValue)
			minValue = i;
	}

	for (int x = 0; x < MAXXDIM; x++)
		for (int y = 0; y < MAXYDIM; y++)
			image_new[x][y] = (int)(255.0 *((float)(image[x][y] - minValue) / (float)(maxValue - minValue)));
		
}

void smoothingHistogram(unsigned char image[MAXXDIM][MAXYDIM], unsigned char image_new[MAXXDIM][MAXYDIM], int grayValues)
{
	unsigned int grayValSet = 0;
	float valuesPerGray = 0;
	float histoVal = 0;
	float histoValWrite = 0;

	//Falls mehr Grauwerte gewünscht sind, als maximal möglich -> 256
	if (grayValues > 256)
		grayValues = 256;

	//Berechnungen
	valuesPerGray = ((float)(MAXXDIM * MAXYDIM) / (float)grayValues);
	histoVal = 256.0 / (float)grayValues;
	
	//Bild neu erzeugen
	for (int i = 0; i < 256; i++)
		for (int x = 0; x < MAXXDIM; x++)
			for (int y = 0; y < MAXYDIM; y++)
			{
				if (image[x][y] == i && histoValWrite < valuesPerGray)
				{
					image_new[x][y] = (int)(histoVal * (float)grayValSet);
					histoValWrite++;
				}

				if (histoValWrite == valuesPerGray)
				{
					grayValSet++;
					histoValWrite = 0;
				}

			}
	



}

/*
typ:	1: 1. Ableitung X
		2: 1. Ableitung Y
		3: 1. Ableitung XY
		4: 2. Ableitung
*/
void derivation(unsigned char image[MAXXDIM][MAXYDIM], unsigned char image_new[MAXXDIM][MAXYDIM], unsigned int typ)
{
	int vx, vy = 0;
	double xy = 0;

	switch (typ)
	{
	case 1: // 1. Ableitung X
		for (int x = 1; x < MAXXDIM - 1; x++)
			for (int y = 1; y < MAXYDIM - 1; y++)
				if ((2 * image[x][y - 1] + image[x + 1][y - 1] + image[x - 1][y - 1]) - (2 * image[x][y + 1] + image[x + 1][y + 1] + image[x - 1][y + 1]) != 0)
					image_new[x][y] = 255;
	break;
	case 2: // 1. Ableitung Y
		for (int x = 1; x < MAXXDIM - 1; x++)
			for (int y = 1; y < MAXYDIM - 1; y++)
				if ((2 * image[x - 1][y] + image[x - 1][y + 1] + image[x - 1][y - 1]) - (2 * image[x + 1][y] + image[x + 1][y + 1] + image[x + 1][y - 1]) != 0)
					image_new[x][y] = 255;
	break;
	case 3: // 1. Ableitung XY

		for (int x = 1; x < MAXXDIM - 1; x++)
			for (int y = 1; y < MAXYDIM - 1; y++)
			{
				vx = (2 * image[x][y - 1] + image[x + 1][y - 1] + image[x - 1][y - 1]) - (2 * image[x][y + 1] + image[x + 1][y + 1] + image[x - 1][y + 1]);
				vy = (2 * image[x - 1][y] + image[x - 1][y + 1] + image[x - 1][y - 1]) - (2 * image[x + 1][y] + image[x + 1][y + 1] + image[x + 1][y - 1]);
				xy = sqrt((vx*vx) + (vy*vy));

				if (xy > 0)
					image_new[x][y] = 255;
			}
	break;
	case 4: // 2. Ableitung
		set_image(image_new, 127);

		for (int x = 1; x < MAXXDIM - 1; x++) {
			for (int y = 1; y < MAXYDIM - 1; y++) {

				if ((image[x - 1][y] + image[x + 1][y] + image[x][y - 1] + image[x][y + 1] - 4 * image[x][y]) > 0)
				{
					image_new[x][y] = 255;
				}
				else if ((image[x - 1][y] + image[x + 1][y] + image[x][y - 1] + image[x][y + 1] - 4 * image[x][y]) < 0)
				{
					image_new[x][y] = 0;
				}
			}
		}
	break;

	default:
		break;
	}
}


void mittelwertfilter(unsigned char image[MAXXDIM][MAXYDIM], unsigned char image_new[MAXXDIM][MAXYDIM], unsigned int filtergroese, unsigned int gewichtung)
{
	int mittelwert = 0;
	int filter2 = filtergroese / 2;

	set_image(image_new, 127);

	
	for (int x = filter2; x < MAXXDIM - filter2; x++)
		for (int y = filter2; y < MAXYDIM - filter2; y++)
		{
			mittelwert = 0;
			for (int n = 0; n < filtergroese; n++)
				for (int i = 0; i < filtergroese; i++)
					mittelwert += image[x - n - 1][y - i - 1];
			mittelwert += image[x][y] * (gewichtung -1);
			image_new[x][y] = mittelwert / ((filtergroese * filtergroese)+(gewichtung-1));
		}
}


void medianfilter(unsigned char image[MAXXDIM][MAXYDIM], unsigned char image_new[MAXXDIM][MAXYDIM], unsigned int filtergroese)
{
	int werte[121];
	int cnt_werte = 0;
	int filter2 = filtergroese / 2;
	set_image(image_new, 127);

		for (int x = filter2; x < MAXXDIM - filter2; x++)
			for (int y = filter2; y < MAXYDIM - filter2; y++)
			{
				cnt_werte = 0;
				for (int n = 0; n < filtergroese; n++)
					for (int i = 0; i < filtergroese; i++)
					{
						werte[cnt_werte] = image[x - n - 1][y - i - 1];
						cnt_werte++;
					}
				bubbleSort(werte, cnt_werte);
				image_new[x][y] = werte[filtergroese*filtergroese/2];
			}
}

void lawsfilter(unsigned char image[MAXXDIM][MAXYDIM], unsigned char image_new[MAXXDIM][MAXYDIM])
{
	int L3L3, L3E3, L3S3, E3L3, E3E3, E3S3, S3L3, S3E3, S3S3;
	double ergebnis;

	emptyImage(image_new);

	for (int x = 1; x < MAXXDIM - 1; x++) {
		for (int y = 1; y < MAXYDIM - 1; y++) {

			L3L3 = (1 * image[x - 1][y - 1] + 2 * image[x - 1][y] + 1 * image[x + 1][y] + 2 * image[x][y - 1] + 4 * image[x][y] + 2 * image[x][y + 1] + 1 * image[x + 1][y - 1] + 2 * image[x + 1][y] + 1 * image[x + 1][y + 1]) / 16;
			L3E3 = (-1 * image[x - 1][y - 1] + 0 * image[x - 1][y] + 1 * image[x + 1][y] - 2 * image[x][y - 1] + 0 * image[x][y] + 2 * image[x][y + 1] - 1 * image[x + 1][y - 1] + 0 * image[x + 1][y] + 1 * image[x + 1][y + 1]);
			L3S3 = (-1 * image[x - 1][y - 1] + 2 * image[x - 1][y] - 1 * image[x + 1][y] - 2 * image[x][y - 1] + 4 * image[x][y] - 2 * image[x][y + 1] - 1 * image[x + 1][y - 1] + 2 * image[x + 1][y] - 1 * image[x + 1][y + 1]);
			E3L3 = (-1 * image[x - 1][y - 1] - 2 * image[x - 1][y] - 1 * image[x + 1][y] + 0 * image[x][y - 1] + 0 * image[x][y] + 0 * image[x][y + 1] + 1 * image[x + 1][y - 1] + 2 * image[x + 1][y] + 1 * image[x + 1][y + 1]);
			E3E3 = (1 * image[x - 1][y - 1] + 0 * image[x - 1][y] - 1 * image[x + 1][y] + 0 * image[x][y - 1] + 0 * image[x][y] + 0 * image[x][y + 1] - 1 * image[x + 1][y - 1] + 0 * image[x + 1][y] + 1 * image[x + 1][y + 1]);
			E3S3 = (1 * image[x - 1][y - 1] - 2 * image[x - 1][y] + 1 * image[x + 1][y] + 0 * image[x][y - 1] + 0 * image[x][y] + 0 * image[x][y + 1] - 1 * image[x + 1][y - 1] + 2 * image[x + 1][y] - 1 * image[x + 1][y + 1]);
			S3L3 = (-1 * image[x - 1][y - 1] - 2 * image[x - 1][y] - 1 * image[x + 1][y] + 2 * image[x][y - 1] + 4 * image[x][y] + 2 * image[x][y + 1] - 1 * image[x + 1][y - 1] - 2 * image[x + 1][y] - 1 * image[x + 1][y + 1]);
			S3E3 = (-1 * image[x - 1][y - 1] + 0 * image[x - 1][y] - 1 * image[x + 1][y] - 2 * image[x][y - 1] + 0 * image[x][y] - 2 * image[x][y + 1] - 1 * image[x + 1][y - 1] + 0 * image[x + 1][y] - 1 * image[x + 1][y + 1]) / 8;
			S3S3 = (1 * image[x - 1][y - 1] - 2 * image[x - 1][y] + 1 * image[x + 1][y] - 2 * image[x][y - 1] + 4 * image[x][y] - 2 * image[x][y + 1] + 1 * image[x + 1][y - 1] - 2 * image[x + 1][y] + 1 * image[x + 1][y + 1]);


			ergebnis = sqrt((L3L3*L3L3) + (L3E3* L3E3) + (L3S3*L3S3) + (E3L3*E3L3) + (E3E3*E3E3) + (E3S3* E3S3) + (S3L3*S3L3) + (S3E3* S3E3) + (S3S3* S3S3));
			if (int(ergebnis) > 255)
				image_new[x][y] = 255;
			else 
				image_new[x][y] = int(ergebnis);
		}
	}
}

unsigned long long fak(unsigned n)
{
	unsigned long long result = 1;
	unsigned i = 1;

	for (; i <= n; ++i)
		result *= i;
	return result;
}

unsigned binominal(unsigned n, unsigned k)
{
	return fak(n) / (fak(k) * fak(n - k));
}

void Pasc_Dreieck(int scale, int Matrix[MAXROW][MAXROW]) {
	int N1[MAXROW] = { 0 };
	int N2[MAXROW] = { 0 };
	int Pasc[MAXROW] = { 0 };

	for (int n = 1; n <= scale + 1; n++) {

		for (int k = 0; k < n; k++) {
			if (k == 0 || k == n - 1) {
				N1[k] = 1;
			}
			else {
				N1[k] = N2[k - 1] + N2[k];
			}
		}
		memcpy(N2, N1, sizeof(N1));

	}
	memcpy(Pasc, N1, sizeof(N1));
	for (int x = 0; x < scale + 1; x++) {
		for (int y = 0; y < scale + 1; y++) {
			Matrix[x][y] = Pasc[x] * Pasc[y];
		}
	}

}

void DoG(unsigned char image[MAXXDIM][MAXYDIM], unsigned char image_new[MAXXDIM][MAXYDIM], int scale) {
	int Matrix1[MAXROW][MAXROW];
	int Matrix2[MAXROW][MAXROW];
	double verteilung1 = 0;
	double verteilung2 = 0;
	double factor1, factor2;

	Pasc_Dreieck(scale, Matrix1);
	Pasc_Dreieck(scale - 2, Matrix2);

	factor1 = pow(2, scale)*pow(2, scale);
	factor2 = pow(2, scale - 2)*pow(2, scale - 2);

	for (int x = (scale / 2); x < MAXXDIM - (scale / 2); x++)
		for (int y = (scale / 2); y < MAXYDIM - (scale / 2); y++)
		{

			for (int x1 = 0; x1 < scale + 1; x1++)
				for (int y1 = 0; y1 < scale + 1; y1++)
					verteilung1 += (image[x - (scale / 2) + x1][y - (scale / 2) + y1] * Matrix1[x1][y1]);

			for (int x2 = 0; x2 < scale - 1; x2++)
				for (int y2 = 0; y2 < scale - 1; y2++)
					verteilung2 += (image[x - ((scale - 2) / 2) + x2][y - ((scale - 2) / 2) + y2] * Matrix2[x2][y2]);

			if ((1.0 / factor1 * verteilung1) - (1.0 / factor2 * verteilung2) > 255)
				image_new[x][y] = 255;
			else
				image_new[x][y] = (1.0 / factor1 * verteilung1) - (1.0 / factor2 * verteilung2);

			verteilung1 = 0;
			verteilung2 = 0;
		}
}

void blobColoring(unsigned char image[MAXXDIM][MAXYDIM], unsigned char image_new[MAXXDIM][MAXYDIM], int toleranz)
{
	emptyImage(image_new);
	int counter = 1;
	int x, y = 0;

	image_new[1][1] = counter;
	for (int x = 1; x < MAXXDIM; x++)
		for (int y = 1; y < MAXYDIM; y++)
			if (abs(image[x][y] - image[x - 1][y]) < toleranz)//gleich dem oberen Wert
			{
				if (image_new[x - 1][y] != 0)
					image_new[x][y] = image_new[x - 1][y];
				else
					image_new[x][y] = counter;

				if (abs(image[x][y] - image[x][y - 1]) < toleranz)
				{//gleich beide
					if (image_new[x - 1][y] == image_new[x][y - 1])
						if (image_new[x - 1][y] != 0)
							image_new[x][y] = image_new[x - 1][y];
						else
							image_new[x][y] = counter;
					else //zwei Flächen verbinden
						if (image_new[x - 1][y] != 0)
						{
							image_new[x][y] = image_new[x - 1][y];

							int p = image_new[x][y - 1];

							for (int g = x - 1; g >= 0; g--)
								for (int h = y; h >= 0; h--)
									if (image_new[g][h] == p)
										image_new[g][h] = image_new[x][y - 1];
						}
						else
							image_new[x][y] = counter;
				}
			}
			else //ungleich oberer Wert
				if (abs(image[x][y] - image[x][y - 1]) < toleranz) // gleich dem unteren Wert
					if (image_new[x][y - 1] != 0)
						image_new[x][y] = image_new[x][y - 1];
					else
						image_new[x][y] = counter;
				else
				{
					counter++;
					image_new[x][y] = counter;
				}

	for (int k = 1; k <= counter; k++)
	{
		int m = 0;
		int a = 0;

		for (int x = 1; x < MAXXDIM - 1; x++)
			for (int y = 1; y < MAXYDIM - 1; y++)
				if (image_new[x][y] == k)
				{
					a++;
					m += image[x][y];
				}

		for (int x = 1; x < MAXXDIM - 1; x++)
			for (int y = 1; y < MAXYDIM - 1; y++)
				if (image_new[x][y] == k)
					image_new[x][y] = (int)((double)m / (double)a);
	}
}