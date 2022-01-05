#define _CRT_SECURE_NO_WARNINGS

#include "Player.h"
#include "Errors.h"
#include "Menu.h"
#include "Gameplay.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

int InitializePlayer(Player player) {
	
	memset(player->name, 0, MAX_NAME);
	memset(player->class, 0, MAX_NAME);
	player->attack = 0;
	player->defense = 0;
	player->health = 0;
	player->luck = 0;
	
	return EXIT_SUCCESS;
}

Player CreatePlayer(int classNumber, char name[MAX_NAME]) {

	Player currentPlayer = NULL;

	currentPlayer = (Player)malloc(sizeof(PlayerStructure)); //alokacija memorije

	InitializePlayer(currentPlayer);
	
	SetName(currentPlayer, name);

	switch (classNumber) {

	case 1: //warrior
		currentPlayer->health = 90;
		currentPlayer->attack = 10;
		currentPlayer->defense = 6;
		strcpy(currentPlayer->class, "Warrior");
		currentPlayer->luck = SetRandomValue(0, 100); //sreca nasumicno odredjena
		break;

	case 2: //mage
		currentPlayer->health = 80;
		currentPlayer->attack = 4;
		currentPlayer->defense = 10;
		strcpy(currentPlayer->class, "Mage");
		currentPlayer->luck = SetRandomValue(0, 100);
		break;

	case 3: //berserker
		currentPlayer->health = 100;
		currentPlayer->attack = 6;
		currentPlayer->defense = 4;
		strcpy(currentPlayer->class, "Berserker");
		currentPlayer->luck = SetRandomValue(0, 100);
		break;

	default: //human
		currentPlayer->health = 30;
		currentPlayer->attack = 2;
		currentPlayer->defense = 1;
		strcpy(currentPlayer->class, "Human");
		currentPlayer->luck = SetRandomValue(0, 100);
		break;
	}

	return currentPlayer;
}

int SetName(Player player, char name[MAX_NAME]) {

	strcpy(player->name, name);

	return EXIT_SUCCESS;
}

int DisplayStatus(Player player) {

	printf("%s\n+-+-+-+-+-+\nCLASS : %s\nHP : %d\nATTACK : %d\nDEFENSE : %d\nLUCK : %d\n", player->name, player->class, player->health, player->attack, player->defense, player->luck);

	return EXIT_SUCCESS;
}

int SetRandomValue(int lowerBound, int upperBound) {

	int value = 0;
	srand(time(0));

	value = rand() % (upperBound - lowerBound + 1) + lowerBound;

	return value;
}

Player ReadCustomPlayer(char* fileName) {

	FILE* fp = NULL;
	char buffer[MAX_LINE_LENGTH] = { 0 }; //medjuspremnik
	int readLine = 0; //br. elemenata u liniji
	int stored_hp = 0, stored_attack = 0, stored_defense = 0, stored_luck = 0; //pricuvane vrij.
	char stored_name[MAX_NAME] = { 0 }, stored_class[MAX_NAME] = { 0 };
	int n = 0; //br. znakova
	int status = EXIT_FAILURE;

	Player customPlayer = NULL;

	fp = fopen(fileName, "r");

	if (fp == NULL)
	{
		system("color C"); perror("\nLoading file failure. . .\n");
		printf("\n>>------>"); system("pause > nul");
		return NULL;
	}

	customPlayer = (Player)malloc(sizeof(PlayerStructure)); //alokacija memorije

	if (!customPlayer) 
	{
		system("color C"); perror("\nMemory allocation failure. . .\n");
		printf("\n>>------>"); system("pause > nul");
		return NULL;
	}

	InitializePlayer(customPlayer);

	while (!feof(fp)) {

		fgets(buffer, MAX_LINE_LENGTH, fp);

		readLine = sscanf(buffer, " %s %s %d %d %d %d %n", stored_name, stored_class, &stored_hp, &stored_attack, &stored_defense, &stored_luck, &n);

		if (readLine == 6)
		{
			strcpy(customPlayer->name, stored_name);
			strcpy(customPlayer->class, stored_class);
			customPlayer->health = stored_hp;
			customPlayer->attack = stored_attack;
			customPlayer->defense = stored_defense;
			customPlayer->luck = stored_luck;
			status = EXIT_SUCCESS;
		}
	}
	
	if (status == EXIT_SUCCESS)
	{
		system("color A"); //zeleno za uspjesnost
		printf("\nFile %s successfully read!\n\n", fileName);
		printf("\n>>------>"); system("pause > nul");
	}

	else
	{
		system("color C");
		printf("\nFile %s not formatted correctly [Name class health attack defense luck]. . .\n", fileName);
		printf("\n>>------>"); system("pause > nul"); fclose(fp);
		return NULL;
	}

	fclose(fp);

	return customPlayer;
}

char* EnterFileName() {

	char* str = NULL;
	str = malloc(sizeof(char) * MAX_NAME);
	printf("\nPlease enter file name:\n\n\t> ");
	scanf(" %s", str);
	return str;
}

char* EnterPlayerName() {

	char* str = NULL;
	str = malloc(sizeof(char) * MAX_NAME);
	printf("\nPlease enter your character's name:\n\n\t> ");
	scanf(" %s", str);
	strtok(str, "\n");
	return str;
}