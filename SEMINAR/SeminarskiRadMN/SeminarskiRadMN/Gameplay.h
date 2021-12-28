#ifndef GAMEPLAY_H
#define GAMEPLAY_H

#include "Save.h"
#include "Inventory.h"
#include "Player.h"
#include "Save.h"
#include "Villain.h"
#include "Map.h"

int Game(Player currentPlayer, Save loadedSave); //pcoetak igre
int EnterWorld(Player currentPlayer, Save currentSaveHead, Villain currentVillainHead, Square currentBoardHead, Item currentInventoryHead, Item currentItemsHead); //ulazak u mapu
Square Move(Player currentPlayer, Square currentPosition, Item currentInventoryHead, Save currentSaveHead, Villain currentVillainHead); //kretanje po mapi/ploci
int FightVillain(PlayerStructure currentPlayer, VillainStructure currentVillain, Item currentInventoryHead); //borba protiv neprijatelja
int LoadedGame(void); //ucitaj igru


#endif