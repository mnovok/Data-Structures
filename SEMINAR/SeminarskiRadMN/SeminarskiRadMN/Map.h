#ifndef MAP_H
#define MAP_H

#include "Map.h"
#include "Player.h"

struct _SquareStructure;

typedef struct _SquareStructure* Square;

typedef struct _SquareStructure {

	char name[MAX_NAME];
	int hasVillain;
	int hasItem;
	Square right;
	Square down;
} SquareStructure;

int InitializeSquare(Square square); //incijalizacija polja
int CreateBoard(Square head, char* fileName); //kreiranje vezane liste za 2D 3x3 mapu ucitavanjem imena polja iz datoteke (posljedni u retku povezan s prvim, posljednji u stupcu povezan s prvim)
Square CreateSquare(void); //kreiranje instance
int InsertSquareAfter(Square current, Square added); //unos iza
int PrintMap(Square head); //ispis cijele mape
int PrintSquare(Square head, Square currentPosition); //ispis trenutne lokacije i susjednih dviju


#endif