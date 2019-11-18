#include <stdio.h>
#include "image-io.h"

void menu()
{
	printf("a) Bild einlesen\n");
	printf("b) Bild speichern\n");
	printf("c) Bild anzeigen\n");
	printf("d) Diletation\n");
	printf("e) Erodieren\n");
	printf("f) Pixel zaehlen\n");
	printf("g) Bilder oeffnen\n");
	printf("h) Bilder schliessen\n");
	printf("i) Grassfire Count\n");
	printf("j) Histogramm\n");
	printf("k) Histogramm dehnen\n");
	printf("l) Histogramm gl�tten\n");
	printf("m) Kanten dedektion\n");
	printf("n) Mittelwert 3x3\n");
	printf("o) Mittelwert 7x7\n");
	printf("p) Medianfilter\n");
	printf("x) Schliessen\n");
}

//Men� Kantendedektion
void menu_derivation()
{
	printf("a) Soebel: X\n");
	printf("b) Soebel: Y\n");
	printf("c) Soebel: XY\n");
	printf("d) 2. Ableitung\n");
	printf("x) Schliessen\n");
}