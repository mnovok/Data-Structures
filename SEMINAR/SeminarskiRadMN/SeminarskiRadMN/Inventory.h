#ifndef INVENTORY_H
#define INVENTORY_H

#include "Player.h"

struct _ItemStructure;

typedef struct _ItemStructure* Item;

typedef struct _ItemStructure {

	char name[MAX_NAME];
	char description[MAX_LINE_LENGTH];
	int index;
	Item next;

} ItemStructure;

int InitializeItem(Item item); //incijalizacija
Item CreateItem(void); //kreiranje instance
int CreateInventoryList(Item head); //2 slobodna mjesta
int InsertItemLast(Item head, Item added); //dodaj na zadnje mjesto
int PrintInventory(Item head); //ispis
int CreateItemsList(Item head); //lista mogucih stvari
Item CreateItemFromFile(char* fileName); //stvaranje iz datoteke
int PrintAllItems(Item head); //ispis svih mogucih stvari
int InventoryIsFull(Item head, Item added); //slucaj kad je spremnik popunjen
int EmptyItem(Item head, int index); //praznjenje cvora
Item FindItemByIndex(Item head, int index); //pretraga
int ReplaceItems(Item head, Item added, int index); //zamjena stvari
int PrintSingleItem(Item item); //ispis jednog itema
int IsInventoryFull(Item head); //provjera popunjenosti spremnika
int AddItem(Item head, Item current); //dodaj stvar
Item FindItemPosition(Item head, int number); //pronadji stvar po poziciji


#endif