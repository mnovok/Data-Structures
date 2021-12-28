#define _CRT_SECURE_NO_WARNINGS

#include "Inventory.h"
#include "Villain.h"
#include "Save.h"
#include "Gameplay.h"
#include "Player.h"
#include "Errors.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

int InitializeSave(Save save) {

	memset(save->name, 0, MAX_NAME);
	//InitializePlayer(&save->savedPlayer);
	//InitializeVillain(&save->savedVillains);
	//InitializeItem(&save->savedInventory);
	save->next = NULL;

	return EXIT_SUCCESS;
}


int InsertSaveAfter(Save current, Save added) {

	added->next = current->next;
	current->next = added;

	return EXIT_SUCCESS;
}

Save CreateSave() {

	Save tempSave = NULL;

	tempSave = (Save)malloc(sizeof(SaveStructure));

	if (!tempSave)
	{
		system("color C"); perror("\nMemory allocation failure. . .\n");
		system("pause > nul");
		return NULL;
	}

	InitializeSave(tempSave);

	return tempSave;
}

int CreateSaveList(Save head) {

	Save first = CreateSave();
	Save second = CreateSave();
	Save third = CreateSave();

	InsertSaveAfter(head, first);
	InsertSaveAfter(first, second);
	InsertSaveAfter(second, third);

	third->next = first;

	return EXIT_SUCCESS;
}

int PrintSaveFiles(Save head) {

	Save first = head->next;
	Save temp = head->next;
	int i = 1;
	int status = 0;

	printf("\nSAVE FILES:\n\n");

	while (i < 4)
	{
		if (strlen(temp->name) == 0)
			printf("%d.\tE M P T Y\n", i);

		else
			printf("%d.\t%s\n", i, temp->name);

		temp = temp->next;
		i++;

		if (temp == first)
			status++;

		if (status == 2) //zadnji save povezan s prvim
			return EXIT_SUCCESS;
	}

	return EXIT_SUCCESS;
}

Save SavePlayer(Player currentPlayer, Villain currentVillainHead, Item currentInventoryHead) {

	Save currentSave = NULL;

	char date[100];

	currentSave = CreateSave();

	time_t now = time(NULL);
	struct tm* t = localtime(&now);

	strftime(date, sizeof(date) - 1, "%d-%m-%Y %H:%M", t);

	currentSave->savedPlayer = currentPlayer;
	currentSave->savedVillains = currentVillainHead;
	currentSave->savedInventory = currentInventoryHead;
	strcpy(currentSave->name, date);
	currentSave->next = NULL;

	return currentSave;
}

int AddSaveFile(Save head, Save currentSave, Save position) {

	if (strlen(position->name) == 0) //ako je cvor prazan
	{
		position->savedPlayer = currentSave->savedPlayer;
		position->savedInventory = currentSave->savedInventory;
		position->savedVillains = currentSave->savedVillains;
		strcpy(position->name, currentSave->name);

		system("color A"); printf("\nGame successfully saved!\n"), system("pause");
	}

	else //postoji savefile
	{
		int choice = 0;
		printf("\nSlot already taken. Do you wish to proceed?\n");
		printf("[ 0 ] - N o\n");
		printf("[ 1 ] - Y e s\n");
		printf("\n\n>\t ");
		scanf(" %d", &choice);

		while (choice != 0 && choice != 1)
		{
			system("color C");
			printf("Please choose something from the menu . . .\n");
			printf("\n\n>\t ");
			scanf(" %d", &choice);
		}

		if (choice == 0)
		{
			system("color C"); printf("\nGame not saved. . .\n"); system("pause");
			return REFUSED_TO_SAVE;
		}

		else
		{
			position->savedPlayer = currentSave->savedPlayer;
			position->savedInventory = currentSave->savedInventory;
			position->savedVillains = currentSave->savedVillains;
			strcpy(position->name, currentSave->name);

			system("color A"); printf("\nSlot overwritten. Game successfully saved!\n"), system("pause");
		}
	}
	return EXIT_SUCCESS;
}

int WriteSaveIntoFile(Save currentSave, char* fileName) {

	FILE* fp = NULL;

	Player currentPlayer = currentSave->savedPlayer;
	Villain villain1 = currentSave->savedVillains->next;
	Villain villain2 = currentSave->savedVillains->next->next;

	fp = fopen(fileName, "w");

	if (strlen(currentSave->name) != 0)
	{
		fprintf(fp, "%s\n", currentSave->name);
		fprintf(fp, "%d %d\n", currentSave->savedInventory->next->index, currentSave->savedInventory->next->next->index);
		fprintf(fp, "%s %s %d %d %d %d\n", currentPlayer->name, currentPlayer->class, currentPlayer->health, currentPlayer->attack, currentPlayer->defense, currentPlayer->luck);
		fprintf(fp, "%s, %s %d %d %d %d\n", villain1->name, villain1->fileName, villain1->health, villain1->attack, villain1->defense, villain1->index);
		fprintf(fp, "%s, %s %d %d %d %d", villain2->name, villain2->fileName, villain2->health, villain2->attack, villain2->defense, villain2->index);
	}

	fclose(fp);

	return EXIT_SUCCESS;
}


int LoadSave(Save temp,  int* item1, int* item2, Villain currentVillainHead, char* saveName) {

	FILE* fp = NULL;
	char buffer[MAX_LINE_LENGTH] = { 0 };
	int playerLine = 0, villainLine = 0;

	Player stored = (Player)malloc(sizeof(PlayerStructure));
	temp->savedPlayer = stored;

	Villain villain1 = currentVillainHead->next;

	fp = fopen(saveName, "r");

	if (fp == NULL)
	{
		system("color C"); perror("\nLoading file failure. . .\n");
		system("pause > nul");
		return NULL;
	}

	else
	{
		rewind(fp); //na pocetak datoteke

		fgets(buffer, MAX_LINE_LENGTH, fp); //naziv datoteke
		strtok(buffer, "\n");
		strcpy(temp->name, buffer);

		fgets(buffer, MAX_LINE_LENGTH, fp); //items
		sscanf(buffer, "%d %d", item1, item2);

		fgets(buffer, MAX_LINE_LENGTH, fp); //o igracu
		playerLine = sscanf(buffer, "%s %s %d %d %d %d", temp->savedPlayer->name, temp->savedPlayer->class, &temp->savedPlayer->health, &temp->savedPlayer->attack, &temp->savedPlayer->defense, &temp->savedPlayer->luck);

		while (!feof(fp))  // o neprijateljima
		{ 
			fgets(buffer, MAX_LINE_LENGTH, fp);
			villainLine = sscanf(buffer, "%[^,], %s %d %d %d %d", villain1->name, villain1->fileName, &villain1->health, &villain1->attack, &villain1->defense, &villain1->index);
			villain1 = villain1->next;
		}
	}

	fclose(fp);

	return EXIT_SUCCESS;

}

int IsSaveEmpty(char* saveName) {

	FILE* fp = NULL;
	int size = 0;

	fp = fopen(saveName, "r");

	if (fp == NULL)
	{
		system("color C"); perror("\nLoading file failure. . .\n");
		system("pause > nul");
		return NULL;
	}

	fseek(fp, 0, SEEK_END);
	size = ftell(fp);

	if (0 == size) //datoteka je prazna
	{
		fclose(fp);
		return EMPTY_SAVE;
	}

	else
	{
		fclose(fp);
		return EXIT_SUCCESS;
	}
}