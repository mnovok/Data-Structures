#ifndef VILLAIN_H
#define VILLAIN_H

#define MAX_NAME (50)

struct _VillainStructure;

typedef struct _VillainStructure* Villain;

typedef struct _VillainStructure {

	char name[MAX_NAME];
	char fileName[MAX_NAME];
	int health;
	int attack;
	int defense;
	int index;
	Villain next;

} VillainStructure;

Villain CreateVillain(char* fileName); //stvaranje instance neprijatelja
int InitializeVillain(Villain villain); //inicijalizacija
int DisplayVillainStats(Villain villain); //ispis statusa
int CreateVillainList(Villain head, char* fileName); //stvori vezanu listu neprijatelja iz datoteke
int InsertVillainAfter(Villain current, Villain added); //dodaj iza
int PrintVillains(Villain head); //ispis svih neprijatelja
Villain SearchVillainByIndex(Villain head, int index); //pronadji neprijatelja pomocu njegova rednoga broja


#endif