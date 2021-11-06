#define _CRT_SECURE_NO_WARNINGS

#include "Functions.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

char* EnterFileName(void)
{
	char* str = NULL;
	str = malloc(sizeof(char) * MAX_SIZE);
	printf("\nUNESITE NAZIV DATOTEKE:\n\t> ");
	scanf(" %s", str);
	return str;
}

Position CreatePolynomial(int coef, int exp)
{
	Position newPolynomial = NULL;

	newPolynomial = (Position)malloc(sizeof(Polynomial));

		if (!newPolynomial)
		{
			system("color C");
			perror("Ne moze se alocirati memorija!\n");
			return -1;
		}

		newPolynomial->koef = coef;
		newPolynomial->pot = exp;
		newPolynomial->next = NULL;

		return newPolynomial;	
}

int InsertAfter(Position position, Position newPolynomial)
{
	newPolynomial->next = position->next;
	position->next = newPolynomial;

	return EXIT_SUCCESS;
}

int InsertSorted(Position head, Position newPolynomial)
{
	Position current = head; //prvi elem. liste
	Position added = newPolynomial; //novi polinom
	int result = 0;
	
		while (current->next != NULL && current->next->pot > added->pot)
			current = current->next;

		if (current->next != NULL && current->next->pot == added->pot)
		{
			current->next->koef += added->koef;
			result = current->koef;

			if(result == 0)
				DeleteNull(current); //ako je zbroj istih koef. 0, izbrisi clan
		}

		else
		{
			CreatePolynomial(added->koef, added->pot);
			InsertAfter(current, added);
		}

	return EXIT_SUCCESS;
}

int PrintList(Position first)
{
	Position temp = first->next;

	while (temp)
	{
		printf("\t%dx*^(%d)\n", temp->koef, temp->pot);
		temp = temp->next;
	}

	puts("");
	return EXIT_SUCCESS;
}


int DeleteNull(Position head)
{
	Position previous = head;
	Position temp = NULL;

	while (previous->next != NULL)
	{
		if (previous->next->koef == 0)
		{
			temp = previous->next;
			previous->next = temp->next;
			free(temp);
		}
		else
			previous = previous->next;
	}
	
	return EXIT_SUCCESS;
}

int ReadLine(Position head, char* buffer)
{
	int coef = 0;
	int exp = 0;
	char* pointer = NULL; //pokazivac na liniju
	int readLine = 0; //vrijednost sscanf
	int n = 0; //broj znakova
	
	pointer = buffer;

	while (strlen(pointer) > 0) //dok pokazivac ne stigne do kraja retka
	{
	
		readLine = sscanf(pointer, " %d %d %n", &coef, &exp, &n);

		if (readLine == 2 && coef != 0) //ukoliko su ucitana dva integera s koef. razl. od 0
				InsertSorted(head, CreatePolynomial(coef, exp));
	
		pointer += n; //sljedeci red	
	}

	return EXIT_SUCCESS;
}

int ReadFile(Position head1, Position head2, char* fileName)
{
	int coef = 0;
	int exp = 0;
	char buffer[MAX_LENGTH] = { 0 };

	FILE* fp = NULL;
	fp = fopen(fileName, "r");

	if (!fp)
	{
		system("color C");
		perror("Pogreska pri ucitavanju datoteke. . .\n");
		system("pause > nul");
		return -1;
	}

	fgets(buffer, MAX_LENGTH, fp);
	ReadLine(head1, buffer);
	DeleteNull(head1);

	fgets(buffer, MAX_LENGTH, fp);
	ReadLine(head2, buffer);
	DeleteNull(head2);

	system("color A");
	printf("\nPodatci uspjesno upisani iz datoteke %s!\n\n", fileName);

	fclose(fp);
	system("pause > nul");

	return EXIT_SUCCESS;
}


int AddPolynomials(Position head1, Position head2, Position headS)
{
	Position p1 = head1->next;
	Position p2 = head2->next;
	Position pS = headS;
	Position temp = NULL;

	while (p1 != NULL && p2 != NULL)
	{
		if (p1->pot > p2->pot)
		{
			InsertSorted(pS, CreatePolynomial(p2->koef, p2->pot));
			p2 = p2->next;
		}

		else if (p1->pot == p2->pot)
		{
			InsertSorted(pS, CreatePolynomial(p1->koef + p2->koef, p1->pot));
			p1 = p1->next;
			p2 = p2->next;
		}

		else // p1 < p2
		{
			InsertSorted(pS, CreatePolynomial(p1->koef, p1->pot));
			p1 = p1->next;
		}
	}

	if (p1 != NULL)
		temp = p1;
	else
		temp = p2;
	while (temp != NULL)
	{
		InsertSorted(pS, CreatePolynomial(temp->koef, temp->pot));
		temp = temp->next;
	}

	DeleteNull(pS);
	
	return EXIT_SUCCESS;
}

int MultiplyPolynomials(Position head1, Position head2, Position headP)
{
	Position p1 = head1->next;
	Position p2 = head2->next;
	Position pP = headP;
	Position start = head2;

	while (p1 != NULL)
	{
		p2 = start; //povratak na prvi clan drugog polinoma
		while (p2 != NULL)
		{
			InsertSorted(pP, CreatePolynomial(p1->koef * p2->koef, p1->pot + p2->pot));
			p2 = p2->next;
		}
		p1 = p1->next;
	}

	DeleteNull(pP);

	return EXIT_SUCCESS;
}

int DeallocateList(Position head)
{
	Position current = head;
	Position temp = NULL;

	if (NULL != current->next) {
		while (NULL != current->next)
		{
			temp = current->next;
			current->next = temp->next;
			free(temp);
		}
		
		return EXIT_SUCCESS; //uspjesno ukoliko lista postoji i prodje petlju
	}

	else
		return EXIT_FAILURE; //neuspjesno ako je lista npr. prazna

}