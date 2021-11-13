#define _CRT_SECURE_NO_WARNINGS

#include "Functions.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char* EnterFileName(void) 
{
	char* str = NULL;
	str = malloc(sizeof(char) * MAX_SIZE);
	printf("\nUNESITE NAZIV DATOTEKE:\n\t> ");
	scanf(" %s", str);
	return str;
}

Position CreateElement(double number)
{
	Position newElement = NULL;

	newElement = (Position)malloc(sizeof(Element));

	if (!newElement)
	{
		system("color C");
		perror("Ne moze se alocirati memorija!\n");
		system("pause > nul");
		return -1;
	}

	newElement->number = number;
	newElement->next = NULL;
	
	return newElement;
}

int InsertAfter(Position position, Position newElement)
{
	newElement->next = position->next;
	position->next = newElement;

	return EXIT_SUCCESS;
}

int DeleteAfter(Position position)
{
	Position top = position->next;

	if (!top)
	{
		return EXIT_SUCCESS; //uspjesno jer nema sto brisati
	}

	position->next = top->next;
	free(top);

	return EXIT_SUCCESS;
}

int PushElement(Position head, double number)
{
	Position newElement = NULL;

	newElement = CreateElement(number);

	if (!newElement)
	{
		system("color C");
		perror("Ne moze se alocirati memorija!\n");
		system("pause > nul");
		return -1;
	}

	InsertAfter(head, newElement);
	
	return EXIT_SUCCESS;
}

int PopElement(double* value, Position head)
{
	Position top = head->next;

	if (!top)
	{
		system("color C");
		perror("Postfiks nije valjan. . .\n");
		system("pause > nul");
		return EXIT_FAILURE;
	}

	*value = top->number; //spremanje brisane vrijednosti

	DeleteAfter(head);

	return EXIT_SUCCESS;
}

int CalculatePostfix(Position head, char operation)
{
	double result = 0.0;
	double top = 0.0;
	double top_prev = 0.0;

	if (PopElement(&top, head) != EXIT_SUCCESS)
	{
		system("color C");
		return EXIT_FAILURE;
	}

	if (PopElement(&top_prev, head) != EXIT_SUCCESS)
	{
		system("color C");
		return EXIT_FAILURE;
	}

	switch (operation)
	{
	case '+':
		result = top_prev + top;
		PrintOperation(top_prev, top, result, operation);
		break;

	case '-':
		result = top_prev - top;
		PrintOperation(top_prev, top, result, operation);
		break;

	case '*':
		result = top_prev * top;
		PrintOperation(top_prev, top, result, operation);
		break;
	
	case '/':
		if (top == 0)
		{
			printf("Ne smije se dijeliti nulom. . . \n");
			break;
		}
		result = top_prev / top;
		PrintOperation(top_prev, top, result, operation);
		break;

	default:
		system("color C");
		printf("\nPOGRESKA! Ova verzija programa sadrzava samo osnovne operacije. . .\nPokusajte s nekom drugom datotekom.\n");
		system("pause > nul");
		DeallocateStack(head);
		ReenterFileName(head);
		break;
	}

	PushElement(head, result);

	return EXIT_SUCCESS;
}

int ReadLine(Position head, char* buffer)
{
	double value = 0.0; //vrijednost broja
	char operation = '\0'; //operacijski znak
	char* currentBuffer = NULL;  //pokazivac na buffer
	int readLine = 0; //vrijednost sscanf
	int byteNumber = 0; //broj bajtova
	int status = 0; //(ne)uspjesnot obavljanja fje

	currentBuffer = buffer;

	while (strlen(currentBuffer) > 0) //dok pokazivac ne stigne do kraja retka
	{
		readLine = sscanf(currentBuffer, " %lf %n", &value, &byteNumber);
	
		if (readLine == 1) //ukoliko je ucitan broj
		{
			status = PushElement(head, value);
			
			if (status != EXIT_SUCCESS) //ako je doslo do greske prilikom pusha
			{
				free(buffer);
				DeallocateStack(head);
				return -3;
			}			
			currentBuffer += byteNumber; //sljedeci clan
		}

		else//ukoliko je ucitan znak, tj. nije broj
		{
			sscanf(currentBuffer, " %c %n", &operation, &byteNumber);

			status = CalculatePostfix(head, operation);

			if (status != EXIT_SUCCESS)
			{
				free(buffer);
				DeallocateStack(head);
				return -3;
			}
			currentBuffer += byteNumber; 
		}
	}
	return EXIT_SUCCESS;
}

int ReadFile(Position head, char* fileName)
{
	int fileLength = 0;
	char* buffer = '\0';

	FILE* fp = NULL;
	fp = fopen(fileName, "rb"); //binarno citanje zbog .exe 

	if(!fp)
	{
		system("color C");
		perror("Pogreska pri ucitavanju datoteke. . .\n");
		system("pause > nul");
		return EXIT_FAILURE;
	}

	fseek(fp, 0, SEEK_END); //pointer na pocetak datoteke
	fileLength = ftell(fp); 

	buffer = (char*)calloc(fileLength + 1, sizeof(char)); //postavljanje svih bajtova na 0

	if (!buffer)
	{
		system("color C");
		perror("Ne moze se alocirati memorija!\n");
		system("pause > nul");
		return -1;
	}

	rewind(fp); //pocetak datoteke

	system("color A"); //zeleno za uspjesnost
	printf("\nPodatci uspjesno upisani iz datoteke %s!\n\n", fileName);

	fread(buffer, sizeof(char), fileLength, fp); //citaj iz fp u buffer 
	printf("\nPOSTFIKS IZGLEDA OVAKO:\n\n\t %s\n", buffer);
	printf("\n~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~\n");
	printf("\nREDOSLIJED RACUNSKIH OPERACIJA:\n");

	fclose(fp);

	ReadLine(head, buffer);

	free(buffer);

	return EXIT_SUCCESS;
}

int PrintOperation(double op1, double op2, double result, char operation)
{
	system("color A");
	printf("\n\t%.2lf", op1); printf(" %c ", operation); printf("%.2lf = %.2lf\n", op2, result);

	return EXIT_SUCCESS;
}

int DeallocateStack(Position head)
{
	Position current = head;
	Position temp = NULL;

	while (current->next != NULL)
	{
		temp = current->next;
		current->next = temp->next;
		free(temp);
	}
	return EXIT_SUCCESS;
}

int ReenterFileName(Position head)
{
	char* fileName = NULL;
	int odabir = 1;

	while (odabir != 0)
	{
		system("cls"); //cisti cmd
		printf("Zelite li pokusati unijeti naziv datoteke jos jednom? [0 ili 1]:\n\n");
		system("color F");
		printf("\tNE -- [ 0 ]\n");
		printf("\tDA -- [ 1 ]\n");
		puts("");
		printf("VAS ODABIR:\n\t> ");
		scanf(" %d", &odabir);

		switch (odabir)
		{
		default:
			system("color C");
			printf("Pogresan unos. . .\n");
			break;

		case 0:
			system("color C");
			break;

		case 1:
			fileName = EnterFileName();
			if (ReadFile(head, fileName) == EXIT_SUCCESS)
			{
				return EXIT_SUCCESS;
				break;
			}
		}
	}
	return EXIT_SUCCESS;
}
