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

int AddFirst(Position head, char* name, char* surname, int birthYear);//dodaje na pocetak liste
int AddLast(Position head, char* name, char* surname, int birthYear);//dodaje na kraj liste
int PrintList(Position first);//ispisuje cijelu listu
Position CreatePerson(char* name, char* surname, int birthYear);//stvara novog studenta
int InsertAfter(Position position, Position newPerson);//dodaje nakon odredjene pozicije
Position FindLast(Position head);//trazi posljednjeg u listi
Position FindBySurname(Position first, char* surname);//samo pronalazak studenta
Position FindBefore(Position first, Position current);//trazi prethodnog
int DeleteAfter(Position head, char* surname);//brise po prezimenu
int PrintStudent(Position person);//ispis odredjenog elementa
int AddPersonAfter(Position head, Position newPerson, char* surname);//dodaje studenta nakon odredjenog elem.
int AddPersonBefore(Position head, Position newPerson, char* surname);//dodaje studenta prije odredjenog elem.
int Sort(Position head);//sortirani unos studenta
char* EnterFileName(void);//unos naziva datoteke
int WriteFile(Position first, char* fileName);//ispisuje u datoteku
int ReadFile(Position first, char* fileName);//ucitava iz datoteke



int main(int argc, char** argv) {

	Person Head = { .next = NULL, .name = {0}, .surname = {0}, .birthYear = 0 };
	Position p = &Head;

	int odabir = 1;
	char name[MAX_SIZE] = { ' ' };
	char surname[MAX_SIZE] = { ' ' };
	char searchedSurname[MAX_SIZE] = { ' ' };
	char* fileName = NULL;
	int birthYear = 0;

	while (odabir != 0)
	{
		system("cls"); //cisti cmd
		PrintList(p);
		printf("Odaberite zeljenu radnju za vezanu listu [0 - 9]:\n\n");
		system("color F");
		printf("\tIzlaz iz programa -- [ 0 ]\n");
		printf("\tUnos studenta na pocetak liste -- [ 1 ]\n");
		printf("\tUnos studenta na kraj liste -- [ 2 ]\n");
		printf("\tPretrazivanje studenata po prezimenu -- [ 3 ]\n");
		printf("\tBrisanje studenta iz liste -- [ 4 ]\n");
		printf("\tDodavanje studenta nakon nekoga drugog -- [ 5 ]\n");
		printf("\tDodavanje studenta prije nekoga drugog -- [ 6 ]\n");
		printf("\tSortirano dodavanje studenata -- [ 7 ]\n");
		printf("\tIspis liste u datoteku -- [ 8 ]\n");
		printf("\tUpis u listu iz datoteke -- [ 9 ]\n");
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
			system("color A");
			printf("\nStudent dodan na pocetak liste. . . \n");
			system("pause > nul");
			break;

		case 2:
			printf("\nUnesite ime i prezime studenta na kraj liste:\n\t> ");
			scanf(" %s %s", name, surname);
			printf("\nUnesite godinu rodjenja studenta:\n\t> ");
			scanf(" %d", &birthYear);
			AddLast(p, name, surname, birthYear);
			system("color A");
			printf("\nStudent dodan na kraj liste. . . \n");
			system("pause > nul");
			break;

		case 3:
			printf("\nUnesite prezime studenta kojega zelite pronaci:\n\t> ");
			scanf(" %s", surname);
			if (FindBySurname(p, surname) != NULL)
				PrintStudent(FindBySurname(p, surname)); //ne ispisuj ako student ne postoji
			break;

		case 4:
			printf("\nUnesite prezime studenta kojega zelite izbrisati:\n\t> ");
			scanf(" %s", surname);
			DeleteAfter(p, surname);
			break;

		case 5:
			printf("\nUnesite prezime studenta iza kojega zelite dodati novog:\n\t> ");
			scanf(" %s", searchedSurname);
			puts("");
			if (FindBySurname(p, searchedSurname) != NULL) //dodaj studenta samo ako postoji trazeno prezime
			{
				printf("\nUnesite ime i prezime studenta kojega zelite dodati:\n\t> ");
				scanf(" %s %s", name, surname);
				printf("\nUnesite godinu rodjenja studenta:\n\t> ");
				scanf(" %d", &birthYear);
				AddPersonAfter(p, CreatePerson(name, surname, birthYear), searchedSurname);
			}
			break;

		case 6:
			printf("\nUnesite prezime studenta prije kojega zelite dodati novog:\n\t> ");
			scanf(" %s", searchedSurname);
			puts("");
			if (FindBySurname(p, searchedSurname) != NULL) //dodaj studenta samo ako postoji trazeno prezime
			{
				printf("\nUnesite ime i prezime studenta kojega zelite dodati:\n\t> ");
				scanf(" %s %s", name, surname);
				printf("\nUnesite godinu rodjenja studenta:\n\t> ");
				scanf(" %d", &birthYear);
				AddPersonBefore(p, CreatePerson(name, surname, birthYear), searchedSurname);
			}
			break;

		case 7:
			printf("\nUnesite ime i prezime studenta kojeg zelite sortirati:\n\t> ");
			scanf(" %s %s", name, surname);
			printf("\nUnesite godinu rodjenja studenta:\n\t> ");
			scanf(" %d", &birthYear);
			SortAdd(p, CreatePerson(name, surname, birthYear));
			break;

		case 8:
			fileName = EnterFileName();
			WriteFile(p, fileName);
			break;

		case 9:
			fileName = EnterFileName();
			ReadFile(p, fileName);
			break;

		default:
			system("color C"); //crvena boja u slucaju greske
			printf("Pogresno unesen broj. . .\n");
			system("pause > nul");
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
	InsertAfter(last, newPerson); //dodajte studenta nakon posljednjeg

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
		system("color C");
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

Position FindBefore(Position first, Position current)
{
	Position previous = NULL;
	Position p = first; //pocetni 

	previous = p; //postavljanje prethodnika na pocetni
	p = p->next; //pocetni postaje sljedeci

	while (NULL != p && strcmp(current->surname, p->surname) != 0)
	{
		previous = p; //kretanje po listi 
		p = p->next;
	}

	if (NULL == p)
		return NULL;
	else
		return previous;
}

int PrintStudent(Position person)
{
	system("color A");
	printf("\nZeljeni student je:\n");
	printf("NAME: %s, SURNAME: %s, BIRTHYEAR: %d\n", person->name, person->surname, person->birthYear);
	system("pause > nul");
}

Position FindBySurname(Position first, char* surname)
{
	Position temp = NULL;
	Position student = NULL;

	for (temp = first->next; temp != NULL; temp = temp->next)
	{
		if (strcmp(temp->surname, surname) == 0)
		{
			return temp;
		}
	}

	system("color C");
	printf("\nTrazeni student ne postoji . . .\n");
	system("pause > nul");

	return NULL;

}

int DeleteAfter(Position head, char* surname)
{
	Position previous = NULL;
	Position current = NULL;
	int deleted = 0;

	for (previous = head; previous->next != NULL; previous = previous->next)

		/*previous = head;			|| za brisanje svih clanova s istim prezimenom, inace brise prvog
		while(previous->next != NULL)*/
	{
		if (strcmp(previous->next->surname, surname) == 0)
		{
			current = previous->next;
			previous->next = previous->next->next;
			free(current);
			system("color A");
			printf("Student uspjesno izbrisan!\n");
			system("pause > nul");
			deleted = 1;
			break;
		}
		/*	else
				previous = previous->next;
			*/
	}

	if (!deleted)
	{
		system("color C");
		printf("Trazeni student ne postoji . . .\n");
		system("pause > nul");
	}

	return EXIT_SUCCESS;
}

int AddPersonAfter(Position head, Position newPerson, char* surname)
{
	Position p = head;
	Position previous = FindBySurname(p, surname);
	Position current = newPerson;

	InsertAfter(previous, current);

	return EXIT_SUCCESS;

}

int AddPersonBefore(Position head, Position newPerson, char* surname)
{
	Position p = head;
	Position current = FindBySurname(p, surname);
	Position added = newPerson;

	added->next = current; //vezivanje dodanog studenta na njegov sljedbenik
	FindBefore(p, current)->next = added; //vezivanje prethodnika od trazenog prezimena na dodanog studenta

	return EXIT_SUCCESS;

}

int SortAdd(Position head, Position newPerson)
{
	Position p = head; //prvi elem. liste
	Position added = newPerson; //osoba koju dodajemo
	Position current = NULL; //trenutna pozicija
	Position previous = NULL; //prethodnik (koristi za fju InsertAfter)

	int swapped = 0;

	while (p->next != NULL)
	{
		p = p->next;
		if (strcmp(p->surname, added->surname) > 0)
		{
			previous = FindBefore(head, p);
			InsertAfter(previous, added);
			system("color A");
			printf("Student uspjesno dodan!\n");
			system("pause > nul");
			return EXIT_SUCCESS;
		}
	}

	AddLast(p, added->name, added->surname, added->birthYear);
	system("color A");
	printf("Student uspjesno dodan!\n");
	system("pause > nul");
	return EXIT_SUCCESS;

}

char* EnterFileName()
{
	char* str = NULL;
	str = malloc(sizeof(char) * 20);
	printf("\nUNESITE NAZIV DATOTEKE:\n\t> ");
	scanf(" %s", str);
	return str;
}

int WriteFile(Position first, char* fileName)
{
	FILE* fp = NULL;
	fp = fopen(fileName, "w");

	Position temp = first->next;

	if (NULL == fp)
	{
		system("color C");
		perror("Pogreska pri ucitavanju datoteke. . .\n");
		system("pause > nul");
		return -2;
	}

	while (temp) {
		fprintf(fp, "NAME: %s, SURNAME: %s, BIRTHYEAR: %d\n", temp->name, temp->surname, temp->birthYear);
		temp = temp->next;
	}

	fclose(fp);

	system("color A");
	printf("Podatci uspjesno ispisani u datoteku %s.\n", fileName);
	system("pause > nul");

	return EXIT_SUCCESS;

}

int ReadFile(Position first, char* fileName)
{
	char name[MAX_SIZE] = { ' ' };
	char surname[MAX_SIZE] = { ' ' };
	int birthYear = 0;

	Position p = first;

	FILE* fp = NULL;
	fp = fopen(fileName, "r");

	if (NULL == fp)
	{
		system("color C");
		perror("Pogreska pri ucitavanju datoteke. . .\n");
		system("pause > nul");
		return -2;
	}

	while (!feof(fp))
	{
		fscanf(fp, "%s %s %d", name, surname, &birthYear);
		AddLast(p, name, surname, birthYear);
	}

	system("color A");
	printf("Podatci uspjesno upisani iz datoteke %s.\n", fileName);
	fclose(fp);
	system("pause > nul");

	return EXIT_SUCCESS;
}