#define _CRT_SECURE_NO_WARNINGS

#include "Map.h"
#include "Villain.h"
#include "Save.h"
#include "Gameplay.h"
#include "Player.h"
#include "Errors.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

int InitializeSquare(Square square) {

	memset(square->name, 0, MAX_NAME);
	square->hasVillain = 0;
	square->hasItem = 0;
	square->right = NULL;
	square->down = NULL;
}

int CreateBoard(Square head, char* fileName) { 

	FILE* fp = NULL;
	int i = 0, j = 0;
	char buffer[MAX_LINE_LENGTH] = { 0 };
	Square matrix[3][3] = { NULL };

	fp = fopen(fileName, "r");

	if (fp == NULL)
	{
		system("color C"); perror("\nLoading file failure. . .\n");
		system("pause > nul");
		return FILE_NOT_OPENED;
	}

	while (!feof(fp)) {

		for (i = 0; i < 3; i++) //povezivanje right pointera
		{
			for (j = 0; j < 3; j++)
			{
				matrix[i][j] = CreateSquare();
				fgets(buffer, MAX_LINE_LENGTH, fp);
				sscanf(buffer, " %s", matrix[i][j]->name);
			}

			for (int k = 0; k < 3; k++)
			{
				if (k < 2)
					matrix[i][k]->right = matrix[i][k + 1];
				else
					matrix[i][k]->right = matrix[i][0];
			}
		}
	}

		for (i = 0; i < 3; i++) { //povezivanje down pointera

			for (j = 0; j < 3; j++)
			{
				if (i < 2)
					matrix[i][j]->down = matrix[i + 1][j];
				else
					matrix[i][j]->down = matrix[0][j];
			}
		}
	
	head->right = matrix[0][0]; //povezanost head-a s matricom
	head->down = matrix[0][0];

	fclose(fp);

	system("color A");
	printf("Map successfully read!\n");

	return EXIT_SUCCESS;

}

Square CreateSquare() {

	Save tempSquare = NULL;

	tempSquare = (Square)malloc(sizeof(SquareStructure));

	if (!tempSquare)
	{
		system("color C"); perror("\nMemory allocation failure. . .\n");
		system("pause > nul");
		return NULL;
	}

	InitializeSquare(tempSquare);

	return tempSquare;
}

int PrintMap(Square head) {

	Square temp = head->right;
	Square first = head->right;
	int status = 0;
	int i = 0;

	while (i < 9) //3x3
	{
		printf("%s\t", temp->name);
		i++;
		temp = temp->right;

		if (temp->right == first)
		{
			printf("%s\t", temp->name);
			puts("");
			i++;
			first = first->down;
			temp = first;
			continue;
		}
	}
	return EXIT_SUCCESS;
}

int PrintSquare(Square head, Square currentPosition) {


	printf("\nYour current position is at:\t%s\n", currentPosition->name);

	printf("\t[ 0 ] Escape menu\n");
	printf("\t[ 1 ] Go right to:\t%s\n", currentPosition->right->name);
	printf("\t[ 2 ] Go down to:\t%s\n\n", currentPosition->down->name);

	return EXIT_SUCCESS;
}

