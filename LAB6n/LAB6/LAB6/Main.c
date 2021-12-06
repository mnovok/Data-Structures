#define _CRT_SECURE_NO_WARNINGS

#include "Bill.h"
#include "Filter.h"

#include <stdio.h>
#include <stdlib.h>
#define MAX_FILE_NAME (1024)

int main(int argc, char** argv) {

	Bill head;
	char* fileName = NULL;
	int odabir = 1;

	BillPosition bp = &head;

	InitializeBill(bp);

	while (odabir != 0)
	{
		system("cls"); //cisti cmd
		system("Color F");
		printf("\tZa izlaz [ 0 ], za filter [ 1 ]\n");

		fileName = EnterFileName();

		ReadBillNamesFromFile(bp, fileName);
		PrintBills(bp);

		puts("");

		printf("VAS ODABIR:\n\t> ");
		scanf(" %d", &odabir);

		switch (odabir)
		{
		case 0:
			break;

		case 1:
			UserSearchArticleInRange(bp);
			break;

		default:
			system("color C"); //crvena boja u slucaju greske
			printf("Pogresno unesen broj. . .\n");
			system("pause > nul");
			break;
		}

		return EXIT_SUCCESS;
	}

	return EXIT_SUCCESS;
}