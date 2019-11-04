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
		case 'A': 
			readImage_ppm(bild);
			break;
		case 'B': 
			writeImage_ppm(bild, 256, 256);
			//writeImage(rueckgabe);
			break;
		case 'C': showImage();
			break;
		case 'D': dilateration(bild, ausgabebild);
			writeImage_ppm(ausgabebild, 256, 256);
			break;
		case 'E': erodieren(bild, ausgabebild);
			writeImage_ppm(ausgabebild, 256, 256);
			break;
		case 'F': printf("Es sind %d Pixel.\n",count_pix(bild));
			getchar();
			//writeImage_ppm(ausgabebild, 256, 256);
			break;
		case 'G':
			printf("Wieviele Zyklen sollen durchlaufen werden?");
			scanf("%i", &anzahl);
			opening(bild, ausgabebild, anzahl);
			writeImage_ppm(ausgabebild, 256, 256);
			break;
		case 'H':
			printf("Wieviele Zyklen sollen durchlaufen werden?");
			scanf("%i", &anzahl);
			closing(bild, ausgabebild, anzahl);
			writeImage_ppm(ausgabebild, 256, 256);
		default:
			break;
		}
		getchar();
		//getchar();

	} while (eingabe != 'X');
}
