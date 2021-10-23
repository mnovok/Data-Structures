#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_SIZE (50)

struct _Person; //deklaracija

typedef struct _Person* Position; // pointer na strukturu _Person

typedef struct _Person 
{
	char name[MAX_SIZE];
	char surname[MAX_SIZE];
	int birthYear;
	Position next; //pointer na sljedecu instancu strukture

} Person;

int AddFirst(Position head, char* name, char* surname, int birthYear);
int AddLast(Position head, char* name, char* surname, int birthYear);
int PrintList(Position first);
Position CreatePerson(char* name, char* surname, int birthYear);
int InsertAfter(Position position, Position newPerson);
Position FindLast(Position head);
int FindBySurname(Position first, char* surname);
Position FindBefore(Position first);
int DeleteAfter(Position head, char* surname);


int main(int argc, char** argv) {

	Person Head = { .next = NULL, .name = {0}, .surname = {0}, .birthYear = 0 };
	Position p = &Head;

	int odabir = 1;
	char name[MAX_SIZE] = {' '};
	char surname[MAX_SIZE] = { ' ' };
	int birthYear = 0;

	while (odabir != 0)
	{
	    system("cls"); //cisti cmd
		PrintList(p);
		printf("Odaberite zeljenu radnju za vezanu listu [0 - 4]:\n");
		printf("\tIzlaz iz programa -- [ 0 ]\n");
		printf("\tUnos studenta na pocetak liste -- [ 1 ]\n");
		printf("\tUnos studenta na kraj liste -- [ 2 ]\n");
		printf("\tPretrazivanje studenata po prezimenu -- [ 3 ]\n");
		printf("\tBrisanje studenta iz liste -- [ 4 ]\n");
		puts("");
		printf("VAS ODABIR:\n\t> ");
		scanf(" %d", &odabir);

		switch (odabir)
		{
		case 0:
			break;

		case 1:
			printf("\nUnesite ime i prezime studenta na pocetak liste:\n\t> ");
			scanf(" %s %s", name, surname);
			printf("\nUnesite godinu rodjenja studenta:\n\t> ");
			scanf(" %d", &birthYear);
			//p = CreatePerson(name, surname, birthYear);
			//InsertAfter(&Head, p);
			AddFirst(p, name, surname, birthYear);
			printf("\nStudent dodan na pocetak liste. . . \n");
			break;

		case 2:
			printf("\nUnesite ime i prezime studenta na kraj liste:\n\t> ");
			scanf(" %s %s", name, surname);
			printf("\nUnesite godinu rodjenja studenta:\n\t> ");
			scanf(" %d", &birthYear);
			AddLast(p, name, surname, birthYear);
			printf("\nStudent dodan na kraj liste. . . \n");
			break;

		case 3:
			printf("\nUnesite prezime studenta kojega zelite pronaci:\n\t> ");
			scanf(" %s", surname);
			FindBySurname(p, surname);
			break;

		case 4:
			printf("\nUnesite prezime studenta kojega zelite izbrisati:\n\t> ");
			scanf(" %s", surname);
			DeleteAfter(p, surname);
			break;
		}
	}

	return EXIT_SUCCESS;
}

int AddFirst(Position head, char* name, char* surname, int birthYear) { //dodavanje studenta na pocetak liste

	Position newPerson = NULL;

	newPerson = CreatePerson(name, surname, birthYear);
	if (!newPerson) {
		return -1;
	}

	InsertAfter(head, newPerson); 

	return EXIT_SUCCESS;
}

int AddLast(Position head, char* name, char* surname, int birthYear) //dodavanje studenta na kraj liste
{
	Position newPerson = NULL;
	Position last = NULL;

	newPerson = CreatePerson(name, surname, birthYear);
	if (!newPerson) {
		return -1;
	}

	last = FindLast(head); // pronadji posljednjeg studenta
	InsertAfter(last, newPerson); //dodajt studenta nakon posljednjeg

	return EXIT_SUCCESS;
}

int PrintList(Position first)
{
	Position temp = first->next;
	printf("\n\tLISTA IZGLEDA OVAKO:\n\n");

	while (temp) {
		printf("NAME: %s, SURNAME: %s, BIRTHYEAR: %d\n", temp->name, temp->surname, temp->birthYear);
		temp = temp->next;
	}

	puts("");
	return EXIT_SUCCESS;
}

Position CreatePerson(char* name, char* surname, int birthYear)
{
	Position newPerson = NULL;

	newPerson = (Position)malloc(sizeof(Person));

	if (!newPerson) 
	{
		perror("Ne moze se alocirati memorija!\n");
		return -1;
	}

	strcpy(newPerson->name, name);
	strcpy(newPerson->surname, surname);
	newPerson->birthYear = birthYear;
	newPerson->next = NULL;

	return newPerson;
}

int InsertAfter(Position position, Position newPerson)
{
	newPerson->next = position->next;
	position->next = newPerson;

	return EXIT_SUCCESS;
}

Position FindLast(Position head)
{
	Position temp = head;

	while (temp->next) 
	{
		temp = temp->next;
	}

	return temp;
}

int FindBySurname(Position first, char* surname)
{
	Position temp = NULL;
	
	for(temp = first->next; temp != NULL; temp = temp->next)
	{
		if (strcmp(temp->surname, surname) == 0) 
		{
			printf("\nZeljeni student je:\n");
			printf("NAME: %s, SURNAME: %s, BIRTHYEAR: %d\n", temp->name, temp->surname, temp->birthYear);
			system("pause > nul");
			break;
		}
	}

	return 0;
}

int DeleteAfter(Position head, char* surname)
{
	Position previous = NULL;
	Position current = NULL;

	for (previous = head; previous->next != NULL; previous = previous->next)
	{
		if (strcmp(previous->next->surname, surname) == 0)
		{
			current = previous->next;
			previous->next = previous->next->next;
			free(current);
			break;
		}
	}
	return 0;
}

