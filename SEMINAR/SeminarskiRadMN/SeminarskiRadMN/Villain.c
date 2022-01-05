#define _CRT_SECURE_NO_WARNINGS

#include "Villain.h"
#include "Player.h"
#include "Errors.h"
#include "Menu.h"
#include "Gameplay.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

int InitializeVillain(Villain villain) {

	memset(villain->name, 0, MAX_NAME);
	memset(villain->fileName, 0, MAX_NAME);
	villain->attack = 0;
	villain->health = 0;
	villain->index = 0;
	villain->next = NULL;

	return EXIT_SUCCESS;
}

Villain CreateVillain(char* fileName) {

	Villain tempVillain = NULL;
	FILE* fp = NULL;
	char buffer[MAX_LINE_LENGTH] = { 0 };

	fp = fopen(fileName, "r");

	if (fp == NULL)
	{
		system("color C"); perror("\nLoading file failure. . .\n");
		system("pause > nul");
		return NULL;
	}

	tempVillain = (Villain)malloc(sizeof(VillainStructure));

	if (!tempVillain)
	{
		system("color C"); perror("\nMemory allocation failure. . .\n");
		system("pause > nul");
		return NULL;
	}

	InitializeVillain(tempVillain);

	fgets(buffer, MAX_LINE_LENGTH, fp); //ucitavanje imena
	strtok(buffer, "\n");
	strcpy(tempVillain->name, buffer);
	fgets(buffer, MAX_LINE_LENGTH, fp); //ucitavanje staze do ASCII datoteke
	strtok(buffer, "\n");
	strcpy(tempVillain->fileName, buffer);
	fgets(buffer, MAX_LINE_LENGTH, fp);
	sscanf(buffer, "%d %d %d %d", &tempVillain->index, &tempVillain->health, &tempVillain->attack, &tempVillain->defense); 

	fclose(fp);

	return tempVillain;
}

int DisplayVillainStats(Villain villain) {

	printf("\n%s\n+-+-+-+-+-+\nHP : %d\nATTACK : %d\nDEFENSE : %d\n", villain->name, villain->health, villain->attack, villain->defense);

	return EXIT_SUCCESS;
}

int CreateVillainList(Villain head, char* fileName) {

	FILE* fp = NULL;
	char buffer[MAX_LINE_LENGTH] = { 0 }; //pohrana imena datoteka neprijatelja

	Villain current = head;

	fp = fopen(fileName, "r");

	if (fp == NULL)
	{
		system("color C"); perror("\nLoading file failure. . .\n");
		printf("\n>>------>"); system("pause > nul");
		return FILE_NOT_OPENED;
	}

	while (!feof(fp))
	{
		Villain tempVillain = NULL;
		fgets(buffer, MAX_LINE_LENGTH, fp); //cita naziv datoteke
		strtok(buffer, "\n"); //brise \n iz imena staze
		tempVillain = CreateVillain(buffer);
		InsertVillainAfter(current, tempVillain);
		current = current->next;
	}
	
	fclose(fp);

	return EXIT_SUCCESS;
}

int InsertVillainAfter(Villain current, Villain added) {

	added->next = current->next;
	current->next = added;

	return EXIT_SUCCESS;
}

int PrintVillains(Villain head) {

	Villain first = head->next;

	printf("\nVillains you shall meet:\n\n");

	while (first)
	{
		printf("%d. %s\n", first->index, first->name);
		first = first->next;
	}

	puts("");

	return EXIT_SUCCESS;
}

Villain SearchVillainByIndex(Villain head, int index) {

	Villain temp = head->next;

	while (temp != NULL && temp->index != index)
		temp = temp->next;

	return temp;
}

