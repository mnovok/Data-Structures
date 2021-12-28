#ifndef MENU_H
#define MENU_H

#include "Map.h"
#include "Save.h"
#include "Villain.h"

int StartGame(void); //pokretanje igre
int Intro(Player currentPlayer, Save loadedSave); //uvod
int Info(void); //opis igre
Player ChooseClass(void); //odabir klase igraca
int DisplayASCII(char filename); //ispis ASCII art iz datoteke
void MaximizeOutputWindow(void); //maksimiranje cmd-a prilikom pokretanja
void RestoreOutputWindow(void); //vracanje na prvobitne postavke
Player ReenterFileName(Player currentPlayer, char* fileName); //ponovni unos imena datoteke
int EscapeMenu(Save saveHead, Player currentPlayer, Villain currentVillainHead, Item currentInventoryHead, Square currentPosition); //meni tijekom igre

#endif 
