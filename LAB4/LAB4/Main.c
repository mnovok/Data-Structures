#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Functions.h"


int main(int argc, char** argv)
{
	Polynomial Head1 = { .next = NULL, .koef = 0, .pot = 0 };
	Polynomial Head2 = { .next = NULL, .koef = 0, .pot = 0 };
	Polynomial HeadS = { .next = NULL, .koef = 0, .pot = 0 };
	Polynomial HeadP = { .next = NULL, .koef = 0, .pot = 0 };

	Position p1 = &Head1;
	Position p2 = &Head2;
	Position pS = &HeadS;
	Position pP = &HeadP;

	char* fileName = NULL;
	int odabir = 1;

	while (odabir != 0)
	{
		system("cls"); //cisti cmd
		printf("Odaberite zeljenu radnju za polinome [0 - 2]:\n\n");
		system("color F");
		printf("\tIzlaz iz programa -- [ 0 ]\n");
		printf("\tZbrajanje polinoma -- [ 1 ]\n");
		printf("\tMnozenje polinoma -- [ 2 ]\n");
		puts("");
		printf("VAS ODABIR:\n\t> ");
		scanf(" %d", &odabir);

		switch (odabir)
		{
		case 0:
			system("color C");
			break;

		case 1:
			fileName = EnterFileName();
			if (ReadFile(p1, p2, fileName) != EXIT_SUCCESS) break;
			printf("\tPOLINOMI SU:\n\n");
			printf("POL. 1:\n");
			PrintList(p1);
			printf("POL. 2:\n");
			PrintList(p2);
			printf("SUMA POLINOMA:\n\n");
			AddPolynomials(p1, p2, pS);
			PrintList(pS);
			system("pause > nul");
			DeallocateList(p1);
			DeallocateList(p2);
			DeallocateList(pS);
			break;
		
		case 2:
			fileName = EnterFileName();
			if (ReadFile(p1, p2, fileName) != EXIT_SUCCESS) break;
			printf("\tPOLINOMI SU:\n\n");
			printf("POL. 1:\n");
			PrintList(p1);
			printf("POL. 2:\n");
			PrintList(p2);
			printf("PRODUKT POLINOMA:\n\n");
			MultiplyPolynomials(p1, p2, pP);
			PrintList(pP);
			system("pause > nul");
			DeallocateList(p1);
			DeallocateList(p2);
			DeallocateList(pP);
			break;

		default:
			system("color C"); //crvena boja u slucaju greske
			printf("Pogresno unesen broj. . .\n");
			system("pause > nul");
			break;
			}
	}

	return EXIT_SUCCESS;
}