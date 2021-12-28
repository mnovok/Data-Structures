#ifndef SAVE_H
#define SAVE_H


#include "Inventory.h"
#include "Player.h"
#include "Villain.h"

struct _SaveStructure;

typedef struct _SaveStructure* Save;

typedef struct _SaveStructure {

	char name[MAX_NAME];
	Player savedPlayer;
	Villain savedVillains;
	Item savedInventory;
	Save next;

} SaveStructure;

int InitializeSave(Save save); //inicijalizacija
int InsertSaveAfter(Save current, Save added); //dodaj save iza
Save CreateSave(void); //alokacija memorije
int CreateSaveList(Save head); //kreiraj listu od 3 cvora
int PrintSaveFiles(Save head); //ispisi listu
Save SavePlayer(Player currentPlayer, Villain currentVillainHead, Item currentInventoryHead); //spremi
int AddSaveFile(Save head, Save currentSave, Save position); //dodaj save, tj. overwriting the existing one
int WriteSaveIntoFile(Save currentSave, char* fileName); //ispis u datoteku (Save1.txt, Save2.txt ili Save3.txt)
int LoadSave(Save temp, int* item1, int* item2, Villain currentVillainHead, char* saveName); //ucitaj save iz datoteke
int IsSaveEmpty(char* saveName); //provjera je li datoteka prazna

#endif