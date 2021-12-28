#define _CRT_SECURE_NO_WARNINGS

#include "Inventory.h"
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

int InitializeItem(Item item) {

	memset(item->name, 0, MAX_NAME);
	memset(item->description, 0, MAX_LINE_LENGTH);
	item->index = 0;
	item->next = NULL;

	return EXIT_SUCCESS;
}

Item CreateItem(void) {

	Item temp = NULL;

	temp = (Item)malloc(sizeof(ItemStructure));

	if (!temp)
	{
		system("color C"); perror("\nMemory allocation failure. . .\n");
		system("pause > nul");
		return NULL;
	}

	InitializeItem(temp);

	return temp;
}

int CreateInventoryList(Item head) {

	Item first = CreateItem();
	Item second = CreateItem();

	InsertItemLast(head, first);
	InsertItemLast(head, second);

	return EXIT_SUCCESS;
	
}

int InsertItemLast(Item head, Item added) {

	Item last = head;

	while (last->next != NULL)
		last = last->next;

	added->next = last->next;
	last->next = added;

	return EXIT_SUCCESS;
}

int PrintInventory(Item head) {

	Item temp = head->next;
	int i = 1;

	printf("\nI N V E N T O R Y\n");
	printf("\nSlot\tName\t Description\n\n");

	while (i < 3)
	{
		if (strlen(temp->name) == 0)
			printf("%d.\tE M P T Y\n", i);
		else
			printf("%d\t%s\t%s\n", i, temp->name, temp->description);
		
		i++;
		temp = temp->next;
	}

	return EXIT_SUCCESS;
}

int CreateItemsList(Item head) {

	FILE* fp = NULL;
	char buffer[MAX_LINE_LENGTH] = { 0 };

	fp = fopen("Inventory/Items.txt", "r");

	if (fp == NULL)
	{
		system("color C"); perror("\nLoading file failure. . .\n");
		system("pause > nul");
		return FILE_NOT_OPENED;
	}

	while (!feof(fp))
	{
		Item temp = NULL;
		fgets(buffer, MAX_LINE_LENGTH, fp);
		strtok(buffer, "\n");
		temp = CreateItemFromFile(buffer);
		InsertItemLast(head, temp);
	}

	fclose(fp);

	return EXIT_SUCCESS;
}

Item CreateItemFromFile(char* fileName) {

	FILE* fp = NULL;
	char buffer[MAX_LINE_LENGTH] = { 0 };
	Item temp = NULL;


	fp = fopen(fileName, "r");

	if (fp == NULL)
	{
		system("color C"); perror("\nLoading file failure. . .\n");
		system("pause > nul");
		return NULL;
	}

	temp = CreateItem();

	fgets(buffer, MAX_LINE_LENGTH, fp); //ucitavanje imena
	strtok(buffer, "\n");
	strcpy(temp->name, buffer);

	fgets(buffer, MAX_LINE_LENGTH, fp); //ucitavanje opisa
	strtok(buffer, "\n");
	strcpy(temp->description, buffer);

	fscanf(fp, "%d", &temp->index); //indeks

	fclose(fp);

	return temp;
}

int PrintAllItems(Item head) {

	Item temp = head->next;

	printf("\nSlot\tName\t Description\n\n");

	while (temp != NULL)
	{
		printf("\n%d\t%s\t%s\n", temp->index, temp->name, temp->description);
		temp = temp->next;
	}

	return EXIT_SUCCESS;
}

int InventoryIsFull(Item head, Item added) {

	Item first = head->next;
	Item second = head->next->next;

	int choice = 2;
	int choice_2 = 0;

	printf("\nInventory is full!\n");
	printf("Do you wish to replace new item with already saved ones?\n");
			
		while (choice != 0 && choice != 1)
			{
				printf("[ 0 ]  N o\n");
				printf("[ 1 ]  Y e s\n");
				printf("\n\t> ");
				scanf("%d", &choice);

				switch (choice)
				{
				case 0:
					break;

				case 1:

					PrintInventory(head);
					printf("\nWhich item do you want it to be replaced with? [1 or 2]\n");
					printf("\n\t> ");
					scanf("%d", &choice_2);
					ReplaceItems(head, added, choice_2);
					break;

				
				default:
					system("color C");
					printf("Please choose something from the menu . . .\n");
					break;
				}
			}

	return EXIT_SUCCESS;
}

int EmptyItem(Item head, int index) {

	Item first = head->next;
	Item second = head->next->next;

	if (index == 1)
	{
		strcpy(first->name, "");
		strcpy(first->name, "");
		first->index = 0;
	}

	else
	{
		strcpy(second->name, "");
		strcpy(second->name, "");
		second->index = 0;
	}

	return EXIT_SUCCESS;
}

Item FindItemByIndex(Item head, int index) {

	Item temp = head->next;

	while (temp != NULL && temp->index != index)
			temp = temp->next;

	return temp;
}

int ReplaceItems(Item head, Item added, int index) {

	Item old = NULL;

	if (index == 1)
		old = head->next;
	else
		old = head->next->next;


	if (old->index != added->index) 
	{
		strcpy(old->name, added->name);
		strcpy(old->description, added->description);
		old->index = added->index;
		system("color A"); printf("Items successfully swapped!\n"); system("pause");
		return EXIT_SUCCESS;
	}

	printf("Two items are the same. . .\n"); system("pause");

	return EXIT_SUCCESS;
}

int PrintSingleItem(Item item) {

	printf("%s\n%s\n", item->name, item->description);

	return EXIT_SUCCESS;
}

int IsInventoryFull(Item head) {

	Item first = head->next;
	Item second = first->next;

	if (strlen(first->name) != 0 && strlen(second->name) != 0)
		return EXIT_SUCCESS;
	else
		return EXIT_FAILURE;
}

int AddItem(Item head, Item current) {

	Item first = head->next;
	Item second = first->next;

	if (strlen(first->name) != 0)
	{
		strcpy(second->name, current->name);
		strcpy(second->description, current->description);
		second->index = current->index;
	}

	else
	{
		strcpy(first->name, current->name);
		strcpy(first->description, current->description);
		first->index = current->index;
	}

	return EXIT_SUCCESS;
}

Item FindItemPosition(Item head, int number) {

	Item first = head->next;
	Item second = head->next->next;

	if (number == 1)
		return first;

	else
		return second;
}