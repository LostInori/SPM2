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
	printf("l) Histogramm glätten\n");
	printf("m) Kanten dedektion\n");
	printf("n) Mittelwert\n");
	printf("o) Medianfilter\n");
	printf("p) Laws Filter\n");
	printf("q) DOG-Operator\n");
	printf("r) BLOB-Coloring\n");
	printf("s) Cooccurrence-Matrix\n");
	printf("x) Schliessen\n");
}

//Menü Kantendedektion
void menu_derivation()
{
	printf("a) Soebel: X\n");
	printf("b) Soebel: Y\n");
	printf("c) Soebel: XY\n");
	printf("d) 2. Ableitung\n");
	printf("x) Schliessen\n");
}