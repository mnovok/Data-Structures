#define _CRT_SECURE_NO_WARNINGS

#include "Save.h"
#include "Gameplay.h"
#include "Player.h"
#include "Errors.h"
#include "Menu.h"
#include "Villain.h"
#include "Map.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>

int StartGame(void) {

    Player currentPlayer = NULL;
    Save loadedSave = NULL;

    Intro(currentPlayer, loadedSave);

    return EXIT_SUCCESS;
}

int Intro(Player currentPlayer, Save loadedSave) {

    int choice = 0;
    char* saveName = NULL;

    system("cls");
    system("color D"); //promjena boje teksta

    DisplayASCII("Art/Intro.txt");

    printf("\n"); printf("\n>>------>"); system("pause > nul"); system("cls"); system("color D");

    while (choice != 4)
    {
        system("cls");
        system("color D");
        
        DisplayASCII("Art/Menu.txt");

        printf("\n\n>\t ");
        scanf(" %d", &choice);

        switch (choice)
        {
        case 1:
            currentPlayer = ChooseClass();
            Game(currentPlayer, loadedSave); //sami gameplay u kojeg saljemo igraca
            break;
        case 2:
            LoadedGame();
            break;
        case 3:
            Info();
            break;
        case 4:
            return EXIT_SUCCESS;
            break;
        default:
            system("color C");
            printf("Please select something from the menu. . .\n");
            printf("\n>>------>"); system("pause > nul");
            break;
        }
    }
    return EXIT_SUCCESS;
}

Player ChooseClass() {

    int choice = 0;
    int classChoice = 0;
    char* fileName = NULL;
    Player currentPlayer = NULL;

    system("cls");
    system("color 6");

    printf("+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+\n\n");
    printf("\t\tDo you want to choose a class or upload your custom stats from a file?\n\n");
    printf("\t\t[ 1 ] C h o o s e  a  c l a s s\n\n"); puts("");
    printf("\t\t[ 2 ] U p l o a d  a  c u s t o m  p l a y e r\n\n"); puts("");
    printf("+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+\n\n");

    printf("\n\n\n>\t ");
    scanf(" %d", &choice);

    while (choice != 1 && choice != 2)
    {
        system("color C");
        printf("Please choose something from the menu . . .\n");
        printf("\n\n>\t ");
        scanf(" %d", &choice);
    }

    system("cls"); system("color 6");

    if (choice == 2)
    {
        fileName = EnterFileName();
        currentPlayer = ReadCustomPlayer(fileName);
        if (currentPlayer == NULL)
            currentPlayer = ReenterFileName(currentPlayer, fileName);   
    }

    else
    {
        printf("+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-++-+-+-+-+-+-+-+-+-+-+-+\n\n");
        printf("\tNow, who do you wish to play as?\n\n"); puts("");
        printf("\t[ 1 ] W a r r i o r ........ focus on attack\n\n"); puts("");
        printf("\t[ 2 ] M a g e .............. focus on defense\n\n"); puts("");
        printf("\t[ 3 ] B e r s e r k e r .... focus on HP\n\n"); puts("");
        printf("\tAnything else results in playing as a mere human! Choose carefully!\n");
        printf("+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-++-+-+-+-+-+-+-+-+-+-+-+\n\n");

        printf("\n\n\n>\t ");
        scanf(" %d", &classChoice);

        currentPlayer = CreatePlayer(classChoice, EnterPlayerName());
    }


    system("cls");  system("color 6");
    DisplayStatus(currentPlayer);
    printf("\n>>------>"); system("pause > nul");

    return currentPlayer;
}

int DisplayASCII(char* fileName) {

    FILE* fp = NULL;
    char buffer[MAX_LINE_LENGTH] = { 0 };

    fp = fopen(fileName, "r");

    while (!feof(fp))
    {
        fgets(buffer, MAX_LINE_LENGTH, fp);
        printf("%s", buffer);
    }

    fclose(fp);

    return EXIT_SUCCESS;
}

void MaximizeOutputWindow(void)
{
    HWND consoleWindow = GetConsoleWindow(); 
    ShowWindow(consoleWindow, SW_MAXIMIZE);
}

void RestoreOutputWindow(void)
{
    HWND consoleWindow = GetConsoleWindow(); 
    ShowWindow(consoleWindow, SW_RESTORE); 
}

int Info() {

    system("cls");

    DisplayASCII("Art/Info.txt");

    printf("\n>>------>"); system("pause > nul");

    return EXIT_SUCCESS;
}

Player ReenterFileName(Player currentPlayer, char* fileName) {

    int choice = 0;

    while (currentPlayer == NULL)
    {
        system("cls");
        printf("Do you wish to reenter file name? [0 or 1]:\n\n");
        system("color 6");
        printf("\t[ 0 ]  N o\n");
        printf("\t[ 1 ]  Y e s\n");
        puts("");
        printf("Your choice:\n\n\t> ");
        scanf(" %d", &choice);

        if (choice == 1)
        {
            fileName = EnterFileName();
            currentPlayer = ReadCustomPlayer(fileName);
        }

        else if (choice == 0)
        {
            StartGame();
            return EXIT_SUCCESS;
        }

        else
        {
            system("color C"); printf("\nWrong command. . .\n");
            printf("\n>>------>"); system("pause > nul");
        }
    }

    return currentPlayer;
}

int EscapeMenu(Save saveHead, Player currentPlayer, Villain currentVillainHead, Item currentInventoryHead, Square currentPosition) {

    int choice = 0;
    int slot = 0;
    Save save = NULL;
    save = CreateSave();
    int item1 = 0, item2 = 0;
   
    Save save1 = saveHead->next;
    Save save2 = saveHead->next->next;
    Save save3 = saveHead->next->next->next;


    if (IsSaveEmpty("Saves/Save1.txt") == EXIT_SUCCESS) //ako nije prazna
        LoadSave(save1, &item1, &item2, currentVillainHead, "Saves/Save1.txt");
    if (IsSaveEmpty("Saves/Save2.txt") == EXIT_SUCCESS)
        LoadSave(save2, &item1, &item2, currentVillainHead, "Saves/Save2.txt");
    if (IsSaveEmpty("Saves/Save3.txt") == EXIT_SUCCESS)
        LoadSave(save3, &item1, &item2, currentVillainHead, "Saves/Save3.txt");


    while (choice != 4)
    {
        system("cls");
        system("color D");

        DisplayASCII("Art/Escape.txt");

        printf("\n\n>\t ");
        scanf(" %d", &choice);

        switch (choice)
        {
        case 1: //spremi igru
            PrintSaveFiles(saveHead);
            printf("Choose slot to save in:\n");
            printf("\n\n>\t ");
            scanf(" %d", &slot);

            switch (slot)
            {
            case 1:
                  save = SavePlayer(currentPlayer, currentVillainHead, currentInventoryHead);
                  AddSaveFile(saveHead, save, save1);
                  WriteSaveIntoFile(save, "Saves/Save1.txt");
                  printf("\n>>------>"); system("pause > nul");
                break;

            case 2:
                save = SavePlayer(currentPlayer, currentVillainHead, currentInventoryHead);
                AddSaveFile(saveHead, save, save2);
                WriteSaveIntoFile(save, "Saves/Save2.txt");
                printf("\n>>------>"); system("pause > nul");
                break;

            case 3:
                save = SavePlayer(currentPlayer, currentVillainHead, currentInventoryHead);
                AddSaveFile(saveHead, save, save3);
                WriteSaveIntoFile(save, "Saves/Save3.txt");
                printf("\n>>------>"); system("pause > nul");
                break;
            default:
                system("color C");
                printf("Please choose something from the menu . . .\n");
                break;
            }

            break;

        case 2: //load game
            system("color d");
            LoadedGame();
            break;
        
        case 3: //nastavi igru
            choice = 4;
            break;

        case 4: //povratak na pocetak igre
            choice = 4;
            exit(0);
            break;
        default:
            system("color C");
            printf("Please select something from the menu. . .\n");
            printf("\n>>------>"); system("pause > nul");
            break;
        }
    }
    return EXIT_SUCCESS;
}

