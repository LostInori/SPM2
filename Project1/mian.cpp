#include <Windows.h>
#include <stdio.h>
#include <conio.h>
#include "menu.h"
#include "funktionen.h"
#include "image-io.h"


int main()
{
	char eingabe;
	unsigned char bild[MAXXDIM][MAXYDIM];
	unsigned char ausgabebild[MAXXDIM][MAXYDIM];
	int rueckgabe = 1;
	int anzahl = 0;
	


	do
	{
		system("cls");
		menu();
		eingabe = getchar();
		eingabe = toupper(eingabe);

		switch (eingabe)
		{
		case 'A': //Bild einlesen
			readImage_ppm(bild);
			break;
		case 'B': //Bild speichern
			writeImage_ppm(bild, 256, 256);
			break;
		case 'C': showImage();
			break;
		case 'D': //Dilate
			dilateration(bild, ausgabebild);
			writeImage_ppm(ausgabebild, 256, 256);
			break;
		case 'E': //Erodieren
			erodieren(bild, ausgabebild);
			writeImage_ppm(ausgabebild, 256, 256);
			break;
		case 'F': //Anzahl Pixel im Bild
			printf("Es sind %d Pixel.\n",count_pix(bild));
			getchar();
			break;
		case 'G': //Opening
			printf("Wieviele Zyklen sollen durchlaufen werden?");
			scanf("%i", &anzahl);
			opening(bild, ausgabebild, anzahl);
			writeImage_ppm(ausgabebild, 256, 256);
			break;
		case 'H': //closing
			printf("Wieviele Zyklen sollen durchlaufen werden?");
			scanf("%i", &anzahl);
			closing(bild, ausgabebild, anzahl);
			writeImage_ppm(ausgabebild, 256, 256);
			break;
		case 'I': //Grassfire
			printf("Es befinden sich %i Objekte aufm Bild." , grassfireCount(bild));
			getchar();
			break;
		case 'J': //Histogramm zeichnen
			drawHistogram(bild, ausgabebild);
			writeImage_ppm(ausgabebild, 256, 256);
			break;
		case 'K': //Stretching Image
			printf("Originalhistogramm wird gespeichert: \n");
			drawHistogram(bild, ausgabebild);
			writeImage_ppm(ausgabebild, 256, 256);
			
			printf("GedehntesBild wird gespeichert: \n");
			stretchingHistogram(bild, ausgabebild);
			writeImage_ppm(ausgabebild, 256, 256);

			printf("Neues Histogramm wird gespeichert: \n");
			drawHistogram(bild, ausgabebild);
			writeImage_ppm(ausgabebild, 256, 256);
			break;
		case 'L': //Histogramm zeichnen
			printf("Wie viele Graustufen soll es geben: ");
			scanf("%i", &anzahl);
			smoothingHistogram(bild, ausgabebild, anzahl);
			writeImage_ppm(ausgabebild, 256, 256);
			break;
		default:
			break;
		}
		getchar();
		//getchar();

	} while (eingabe != 'X');
}
