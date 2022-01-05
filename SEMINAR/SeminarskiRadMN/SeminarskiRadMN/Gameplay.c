#define _CRT_SECURE_NO_WARNINGS

#include "Inventory.h"
#include "Map.h"
#include "Save.h"
#include "Gameplay.h"
#include "Villain.h"
#include "Player.h"
#include "Errors.h"
#include "Menu.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

int Game(Player currentPlayer, Save loadedSave) {

    system("cls"); printf("\nL o a d i n g . . .\n\n");

    DisplayStatus(currentPlayer);

    VillainStructure HeadV = { .name = { 0 }, .fileName = { 0 }, .attack = 0, .defense = 0, .health = 0, .index = 0, .next = NULL };
    Villain VillainHead = &HeadV; //vezana lista

    Villain first = HeadV.next;

    CreateVillainList(VillainHead, "Art/Villains/VillainList.txt"); //kreiranje liste iz datoteke
    PrintVillains(VillainHead); 

    SaveStructure HeadS = { .name = {0}, .savedPlayer = NULL, .savedVillains = NULL, .savedInventory = NULL, .next = NULL };
    Save SaveHead = &HeadS;

   CreateSaveList(SaveHead);
   
    SquareStructure HeadSq = { .name = {0}, .hasItem = 0, .hasVillain = 0, .right = NULL, .down = NULL };
    Square SquareHead = &HeadSq;


    CreateBoard(SquareHead, "Art/Map.txt");
    PrintMap(SquareHead);


    ItemStructure HeadIn = { .name = {0}, .description = {0}, .index = 0, .next = NULL };
    Item InventoryHead = &HeadIn;

    CreateInventoryList(InventoryHead);
    PrintInventory(InventoryHead);

    ItemStructure HeadIt = { .name = {0}, .description = {0}, .index = 0, .next = NULL };
    Item ItemHead = &HeadIt;

    CreateItemsList(ItemHead);
    PrintAllItems(ItemHead);

    //PrintSaveFiles(SaveHead);

    printf("\nEverything loaded successfully! How sweet!\n");

    printf("\n>>------>"); system("pause > nul");

    EnterWorld(currentPlayer, SaveHead, VillainHead, SquareHead, InventoryHead, ItemHead);

    return EXIT_SUCCESS;
}


int EnterWorld(Player currentPlayer, Save currentSaveHead, Villain currentVillainHead, Square currentBoardHead,  Item currentInventoryHead, Item currentItemsHead) {

    system("color d"); system("cls");
    printf("\nW E L C O M E  T O  L I N K E D  L A N D  L O O !\n\n");
    printf("\nOn your endless journey, you will face nine different villains at nine possible locations!\n\n");
    printf("\nYou can also store up to two items in your mini backpack!\n\n");
    DisplayASCII("Art/LinkedLandLoo.txt"); printf("\n");
    printf("\nGood luck %s!\n", currentPlayer->name);

    printf("\n>>------>"); system("pause > nul");

    int fight = 0;

    Square currentPosition = currentBoardHead->right;
    
    PlayerStructure originalPlayer = *currentPlayer;
    
    //PrintSquare(currentBoardHead, currentPosition);

    while (1) {

        system("color d"); system("cls"); puts("");

        PrintMap(currentBoardHead); puts("");

        PrintSquare(currentBoardHead, currentPosition);

        currentPosition = Move(currentPlayer, currentPosition, currentInventoryHead, currentSaveHead, currentVillainHead);

        int villain = 0, hasVillain = 0, item = 0, hasItem = 0, choice = 2;
        Villain currentVillain = NULL;

        villain = SetRandomValue(1, 9);
        hasVillain = SetRandomValue(0, 100);

        Item currrentItem = NULL;

        hasItem = SetRandomValue(0, 100);
        item = SetRandomValue(1, 5);

        if (hasItem < 60) //pojavit ce se item
        {
            system("color b");
            currrentItem = FindItemByIndex(currentItemsHead, item);
            printf("\nA magical potion has dropped!\n\n");
            PrintSingleItem(currrentItem);
            printf("\nDo you wish to take it?\n");

            while (choice != 0 && choice != 1)
            {
                printf("[ 0 ]  N o\n");
                printf("[ 1 ]  Y e s\n");
                printf("\n\t> ");
                scanf("%d", &choice);

                switch (choice)
                {
                default:
                    system("color C");
                    printf("Please choose something from the menu . . .\n");
                    break;

                case 0:
                    break;

                case 1:
                    if (IsInventoryFull(currentInventoryHead) == EXIT_SUCCESS)
                        InventoryIsFull(currentInventoryHead, currrentItem);
                    else
                        AddItem(currentInventoryHead, currrentItem);
                    printf("\n>>------>"); system("pause > nul");
                    break;

                }
            }
        }
        
        if (hasVillain <= 70) //pojavit ce se neprijatelj
        {
            currentPosition->hasVillain = 1;
            currentVillain = SearchVillainByIndex(currentVillainHead, villain);
            VillainStructure originalVillain = *currentVillain;
            system("color 4");
            printf("\n\n%s has appeared! You must defeat them!\n", currentVillain->name);
            printf("\n>>------>"); system("pause > nul");

            fight = FightVillain(originalPlayer, originalVillain, currentInventoryHead);

            if (fight == EXIT_SUCCESS)
            {
                currentPlayer->health += 2;
                currentPlayer->attack += 1;
                currentPlayer->defense += 1;
                printf("\n%s has gotten stronger!\n", currentPlayer->name);
            }

            else
            {
                currentVillain->health += 2;
                currentVillain->attack += 1;
                currentVillain->defense += 1;
                printf("\nOh no! %s has gotten stronger. . .\n", currentVillain->name);
            }       
            printf("\n>>------>"); system("pause > nul");
        }
    }

    return EXIT_SUCCESS;
}

Square Move(Player currentPlayer, Square currentPosition, Item currentInventoryHead, Save head, Villain currentVillainHead) {

    int direction = 3;
    Square newPosition = NULL;

    while (direction < 0 || direction > 2) {
   
        printf("Enter your choice:\n");
        printf("\n\n>\t ");
        scanf(" %d", &direction);

        switch (direction)
        {
        case 0:
            EscapeMenu(head, currentPlayer, currentVillainHead, currentInventoryHead, currentPosition);
            direction = 3;
            return currentPosition;
            break;
        case 1:
            newPosition = currentPosition->right;
            break;
        case 2:
            newPosition = currentPosition->down;
            break;
        default:
            system("color C");
            printf("Please choose something from the menu . . .\n");
            break;
        }
    }

    return newPosition;
}


int FightVillain(PlayerStructure currentPlayer, VillainStructure currentVillain, Item currentInventory) {

    int option = 0;
    PlayerStructure Player = currentPlayer;
    VillainStructure Villain = currentVillain;
    Item currentItem = NULL;
    int option_2 = 2;
    int potion = 0;


    while (Player.health > 0 && Villain.health > 0)
    {
        system("cls");  system("color D");
        printf("\t\t %s %s fighting against %s\n\n", Player.class, Player.name, Villain.name);
        DisplayASCII(Villain.fileName);
        puts("");

        DisplayStatus(&Player);
        puts(" ");
        DisplayVillainStats(&Villain);

        printf("\n[ 1 ]  F i g h t\n");
        printf("\n[ 2 ]  D e f e n d\n");
        printf("\n[ 3 ]  U s e  i t e m\n");
        printf("\n\t> ");
        scanf("%d", &option);

        switch (option)
        {
        case 1:

            if (SetRandomValue(0, 200) >= SetRandomValue(0, 40))
            {            
                Villain.health -= Player.attack;
                printf("\nAttacking!\n%s has lost %d HP!\n", Villain.name, Player.attack);
            }

            else 
                printf("\nAttacking!\n%s uses defense and has dodged the attack!\n", Villain.name);
           
            puts("");
            system("pause > nul");
            puts("");

            if (Player.luck > SetRandomValue(80, 100))
            {
                int hp = 0;

                hp = Villain.attack;
                Player.health -= hp;

                if (Player.defense > Villain.attack)
                {
                    hp = Player.defense - Villain.attack;
                    if (hp == 0)
                        hp = 1;
                    Player.health -= hp;       
                }

                printf("Getting attacked!\n%s has lost %d HP!\n", Player.name, hp);
            }

            else
            {
                Player.health -= Villain.attack;
                printf("Getting attacked!%s has lost %d HP!\n", Player.name, Villain.attack);
            }

            system("pause > nul");
            break;

        case 2:
            if (Player.luck < SetRandomValue(0, 200))
            {
                printf("%s has dodged %s's attack!\n", Player.name, Villain.name);
                system("pause > nul");
            }
            else
            {
                Player.health -= Villain.attack;
                printf("Defense failed! %s has taken %d damage!\n", Player.name, Villain.attack);
                system("pause > nul");
            }
            break;

        case 3:
            PrintInventory(currentInventory);
                printf("\nChoose item to use!\n");
                printf("\n\t> "); scanf("%d", &option_2);
                int hp = 0;
                switch (option_2)
                {
                default:
                    Player.health -= Villain.attack;
                    printf("Oops! Getting attacked! %s has taken %d damage!\n", Player.name, Villain.attack);
                    break;

                case 1: case 2:
                    currentItem = FindItemPosition(currentInventory, option_2);
                    potion = currentItem->index;
                    switch (potion)
                    {
                    case 1:
                        hp = 0.1 * Player.health;
                        Player.health += hp;
                        printf("Mercy from above! %s has restored %d HP\n", Player.name, hp);
                        EmptyItem(currentInventory, option_2); 
                        system("pause > nul"); puts("");
                        Player.health -= Villain.attack;
                        printf("Getting attacked! %s has taken %d damage!\n", Player.name, Villain.attack); system("pause");
                        break;

                    case 2:
                        Villain.health -= (2 * Player.attack);
                        printf("Lightning strike! %s has lost %d HP!\n", Villain.name, 2 * Player.attack);
                        EmptyItem(currentInventory, option_2);
                        system("pause > nul"); puts("");
                        Player.health -= Villain.attack;
                        printf("Getting attacked! %s has taken %d damage!\n", Player.name, Villain.attack); system("pause");
                        break;

                    case 3:
                        if (SetRandomValue(0, 100) < SetRandomValue(0, 70))
                        {
                            Villain.health -= Player.attack;
                            printf("Attacking! %s has lost %d HP!\n", Villain.name, Player.attack);
                            EmptyItem(currentInventory, option_2);
                            system("pause > nul"); puts("");
                            Villain.health -= Villain.attack;
                            printf("Ha ha ha! %s really attacked THEMSELVES and lost %d HP!\n", Villain.name, Villain.attack);
                        }

                        else
                        {
                            Villain.health -= Player.attack;
                            printf("Attacking! %s has lost %d HP!\n", Villain.name, Player.attack);
                            EmptyItem(currentInventory, option_2);
                            system("pause > nul"); puts("");
                            Player.health -= (2 * Player.attack);
                            printf("Silly %s attacked themselves by mistake and lost %d HP!\n", Player.name, 2 * Player.attack);
                        }
                        system("pause > nul");
                        break;

                    case 4:
                        Player.defense += 3;
                        printf("How lovely! %s's defense has incread to %d!\n", Player.name, Player.defense);
                        system("pause");
                        Villain.health -= Player.attack;
                        printf("Attacking! %s has lost %d HP!\n", Villain.name, Player.attack);
                        EmptyItem(currentInventory, option_2);
                        system("pause > nul"); puts("");
                        Player.health -= Villain.attack;
                        printf("Getting attacked! %s has lost %d HP!\n", Player.name, Villain.attack);  system("pause");
                        break;
                    
                    case 5:
                        if (50 >= SetRandomValue(0, 100))
                        {
                            Villain.health -= (Villain.health / 2);
                            printf("Nice gamble! %s has lost half of their HP!\n", Villain.name);
                        }
                        else
                        {
                            Player.health -= (Villain.health / 2);
                            printf("Tough luck! %s has lost half of their HP!\n", Player.name);
                        }
                        EmptyItem(currentInventory, option_2);
                        system("pause > nul");
                        break;
                    }
                }

            break;

        default:
            system("color C");
            printf("Please choose something from the menu . . .\n"); system("pause > nul");
            break;

        }
    }

    if (Player.health > 0)
    {
        system("color A");
        printf("\n%s has successfully defeated %s!\n", Player.name, Villain.name);
        printf("\n>>------>"); system("pause > nul");;
        return EXIT_SUCCESS;

    }

    else
    {
        system("color C");
        printf("\n%s has been defeated by %s. . .\n", Player.name, Villain.name);
        printf("\n>>------>"); system("pause > nul");
        return EXIT_FAILURE;
    }
}

int LoadedGame() {

    system("cls");

    VillainStructure HeadV = { .name = { 0 }, .fileName = { 0 }, .attack = 0, .defense = 0, .health = 0, .index = 0, .next = NULL };
    Villain VillainHead = &HeadV; //vezana lista

    CreateVillainList(VillainHead, "Art/Villains/VillainList.txt"); //kreiranje liste iz datoteke

    SaveStructure HeadS = { .name = {0}, .savedPlayer = NULL, .savedVillains = NULL, .savedInventory = NULL, .next = NULL };
    Save SaveHead = &HeadS;

    CreateSaveList(SaveHead);

    SquareStructure HeadSq = { .name = {0}, .hasItem = 0, .hasVillain = 0, .right = NULL, .down = NULL };
    Square SquareHead = &HeadSq;

    CreateBoard(SquareHead, "Art/Map.txt");

    ItemStructure HeadIn = { .name = {0}, .description = {0}, .index = 0, .next = NULL };
    Item InventoryHead = &HeadIn;

    CreateInventoryList(InventoryHead);

    ItemStructure HeadIt = { .name = {0}, .description = {0}, .index = 0, .next = NULL };
    Item ItemHead = &HeadIt;

    CreateItemsList(ItemHead);

    int item1 = 0, item2 = 0; //indeksi spremljenih itemsa
    int choice = 4;

    Save save1 = SaveHead->next;
    Save save2 = SaveHead->next->next;
    Save save3 = SaveHead->next->next->next;

    if (IsSaveEmpty("Saves/Save1.txt") == EXIT_SUCCESS) //ako nije prazna
        LoadSave(save1, &item1, &item2, VillainHead, "Saves/Save1.txt");
    if (IsSaveEmpty("Saves/Save2.txt") == EXIT_SUCCESS)
        LoadSave(save2, &item1, &item2, VillainHead, "Saves/Save2.txt");
    if (IsSaveEmpty("Saves/Save3.txt") == EXIT_SUCCESS)
        LoadSave(save3, &item1, &item2, VillainHead, "Saves/Save3.txt");

    while (1)
    {
        system("cls");
        PrintSaveFiles(SaveHead);
        puts("");
        printf("Choose savefile to load [1, 2, 3 or 0 for MAIN MENU]\n");
        printf("\n\t> ");
        scanf("%d", &choice);

        switch(choice)
        {
        case 1:
            if (IsSaveEmpty("Saves/Save1.txt") == EXIT_SUCCESS)
            {
                LoadSave(save1, &item1, &item2, VillainHead, "Saves/Save1.txt");
                system("color A"); printf("Savefile successfully loaded!\n"); system("pause");
                if (item1 != 0)
                    AddItem(InventoryHead, FindItemByIndex(ItemHead, item1));
                if(item2 != 0)
                    AddItem(InventoryHead, FindItemByIndex(ItemHead, item2));
                EnterWorld(save1->savedPlayer, SaveHead, VillainHead, SquareHead, InventoryHead, ItemHead);
                break;
            }
            else
            {
                system("color C"); printf("That save file is empty!\nChoose another one or go back to main menu. . .\n");
                printf("\n>>------>"); system("pause > nul");
                break;
            }
        
        case 2:
            if (IsSaveEmpty("Saves/Save2.txt") == EXIT_SUCCESS)
            {
                LoadSave(save2,  &item1, &item2, VillainHead, "Saves/Save2.txt");
                system("color A"); printf("Savefile successfully loaded!\n");  system("pause");
                if (item1 != 0)
                    AddItem(InventoryHead, FindItemByIndex(ItemHead, item1));
                if (item2 != 0)
                    AddItem(InventoryHead, FindItemByIndex(ItemHead, item2));
                EnterWorld(save2->savedPlayer, SaveHead, VillainHead, SquareHead, InventoryHead, ItemHead);
                break;
            }
            else
            {
                system("color C"); printf("That save file is empty!\nChoose another one or go back to main menu. . .\n");
                printf("\n>>------>"); system("pause > nul");
                break;
            }
        
        case 3:
            if (IsSaveEmpty("Saves/Save3.txt") == EXIT_SUCCESS)
            {
                LoadSave(save3, &item1, &item2, VillainHead, "Saves/Save3.txt");
                system("color A"); printf("Savefile successfully loaded!\n");  system("pause");
                if (item1 != 0)
                    AddItem(InventoryHead, FindItemByIndex(ItemHead, item1));
                if (item2 != 0)
                    AddItem(InventoryHead, FindItemByIndex(ItemHead, item2));
                EnterWorld(save3->savedPlayer, SaveHead, VillainHead, SquareHead, InventoryHead, ItemHead);
                break;
            }
            else
            {
                system("color C"); printf("That save file is empty!\nChoose another one or go back to main menu. . .\n");
                printf("\n>>------>"); system("pause > nul");
                break;
            }

        case 0:
            StartGame();
            break;
        
        default:
            system("color C");
            printf("Please choose something from the menu . . .\n"); printf("\n>>------>"); system("pause > nul");
            break;

        }
    }

    printf("\n>>------>"); system("pause > nul");

    return EXIT_SUCCESS;
}