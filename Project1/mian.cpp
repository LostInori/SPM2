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
	int anzahl2 = 0;
	


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
		case 'M': //Derivation
			system("cls");
			getchar();
			menu_derivation();
			eingabe = getchar();
			eingabe = toupper(eingabe);
			switch (eingabe)
			{
				case 'A':
					derivation(bild, ausgabebild, 1);
					writeImage_ppm(ausgabebild, MAXXDIM, MAXYDIM);
				break;
				case 'B':
					derivation(bild, ausgabebild, 2);
					writeImage_ppm(ausgabebild, MAXXDIM, MAXYDIM);
				break;
				case 'C':
					derivation(bild, ausgabebild, 3);
					writeImage_ppm(ausgabebild, MAXXDIM, MAXYDIM);
				break;
				case 'D':
					derivation(bild, ausgabebild, 4);
					writeImage_ppm(ausgabebild, MAXXDIM, MAXYDIM);
				break;
			default:
				if (eingabe != 'X')
					printf("Falsche Eingabe");
				break;
			}
			break;
		case 'N': //Mittelwert
			printf("Filtergroeße (ungerade): ");
			scanf("%i", &anzahl2);
			printf("\nMit welchem Faktor soll der Mittelpunkt gewichtet werden?: ");
			scanf("%i", &anzahl);
			if ((anzahl2 % 2) > 0 && anzahl2 >= 3)
			{
				mittelwertfilter(bild, ausgabebild, anzahl2, anzahl);
				writeImage_ppm(ausgabebild, MAXXDIM, MAXYDIM);
			}
			else
			{
				printf("Die Filtergroesse muss ungerade sein und groesser als 3.\n");
				getchar();
			}
		break;
		case 'O': //Medianfilter
			printf("Filtergroeße (ungerade): ");
			scanf("%i", &anzahl);
			if ((anzahl % 2) > 0 && anzahl >= 3 && anzahl <=11)
			{
				medianfilter(bild, ausgabebild, anzahl);
				writeImage_ppm(ausgabebild, MAXXDIM, MAXYDIM);
			}
			else
			{
				printf("Die Filtergroesse muss ungerade sein und groesser als 3.\n");
				getchar();
			}
			break;
		case 'P': //Laws Filter
			lawsfilter(bild, ausgabebild);
			writeImage_ppm(ausgabebild, MAXXDIM, MAXYDIM);
			break;
		case 'Q': //DOG-Operator
			printf("n: ");
			scanf("%i", &anzahl);
			if ((anzahl % 2) == 0 && anzahl <= 100)
			{
				DoG(bild, ausgabebild, anzahl);
				writeImage_ppm(ausgabebild, MAXXDIM, MAXYDIM);
			}
			else
			{
				printf("Der Wert 'n' entspricht den Erwartungen.");
				getchar();
			}
			break;
		case 'R':
			printf("Toleranz: ");
			scanf("%i", &anzahl);
			blobColoring(bild, ausgabebild, anzahl);
			writeImage_ppm(ausgabebild, MAXXDIM, MAXYDIM);
			break;
		default:
			break;
		}
		getchar();
		//getchar();

	} while (eingabe != 'X');
}
