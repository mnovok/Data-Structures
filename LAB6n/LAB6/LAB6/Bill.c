#define _CRT_SECURE_NO_WARNINGS
#include "Bill.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LENGTH (1024)

int InitializeBill(BillPosition bP) {

	bP->next = NULL;
	bP->date = NULL;
	memset(bP->name, 0, MAX_BILL_NAME);
	InitializeArticle(&bP->articleHead);

	return EXIT_SUCCESS;
}

BillPosition FindBefore(BillPosition head, BillPosition current) {

	BillPosition previous = NULL;
	BillPosition p = head;

	previous = p;
	p = p->next;

	while (p != NULL && DateCompare(current->date, p->date) != 0)
	{
		previous = p;
		p = p->next;
	}

	if (NULL == p)
		return NULL;

	else
		return previous;
}

int InsertBillAfter(BillPosition current, BillPosition added) {

	added->next = current->next;
	current->next = added;

	return EXIT_SUCCESS;
}

int ReadBillNamesFromFile(BillPosition head, char* fileName) {

	char buffer[MAX_LENGTH] = { 0 };

	FILE* fp = NULL;
	fp = fopen(fileName, "r");

	if (!fp)
	{
		system("color C"); perror("Pogreska pri ucitavanju datoteke. . .\n"); system("pause > nul");
		ReenterFileName(head); //mogucnost ponovnog unosa imena datoteke
		return -1;
	}

	while (!feof(fp)) //do kraja datoteke
	{
		BillPosition bill = NULL;

		fscanf(fp, "%s", buffer); //citaj string iz retka

		if (strlen(buffer) == 0)
			continue;

		bill = ReadBillData(head, buffer); //udji u svaku navedenu datoteku

		if (!bill)
		{
			fclose(fp);
			DeleteAllBills(head);
			return -3;
		}

		InsertBillSorted(head, bill);
	}

	system("color A"); printf("\nPodatci uspjesno upisani iz datoteke %s!\n\n", fileName);

	fclose(fp); system("pause > nul");

	return EXIT_SUCCESS;
}

BillPosition ReadBillData(BillPosition head, char* billName) {

	int year = 0; int month = 0; int day = 0;
	char name[MAX_LENGTH] = { 0 }; int count = 0; float price = 0.0f;
	char stored_date[MAX_LENGTH] = { 0 };
	char stored_article[MAX_LENGTH] = { 0 };

	BillPosition bill = NULL;

	FILE* fp = NULL;

	fp = fopen(billName, "r");

	if (!fp)
	{
		system("color C"); perror("Pogreska pri ucitavanju datoteke. . .\n"); system("pause > nul");
		ReenterFileName(head); //mogucnost ponovnog unosa imena datoteke
		return -1;
	}

	bill = (BillPosition)malloc(sizeof(Bill));

	if (!bill)
	{
		system("Color C"); perror("Racun se ne moze alocirati. . .\n");
		fclose(fp);
		return NULL; //fja vraca pokazivac
	}

	InitializeBill(bill);

	strcpy(bill->name, billName); //naziv racuna

	fgets(stored_date, MAX_LENGTH, fp); //prvi redak je datum

	if (sscanf(stored_date, " %d-%d-%d", &year, &month, &day) == 3) //ako je ispravan format datuma
		bill->date = CreateDate(stored_date); //stvori datum iz stringa

	else
	{
		system("Color C"); printf("Pogresno unesen datum [YYYY-MM-DD]. . .\n"); system("pause > nul");
		fclose(fp); DeleteBill(bill);
		return NULL;
	}

	while (!feof(fp))
	{
		ArticlePosition article = NULL;
		fgets(stored_article, MAX_LENGTH, fp); //cita retke s artiklima, kol. i cijenom

		if (strlen(stored_article) == 0)
			continue;

		article = CreateArticle(stored_article); //kreira cvor artikla

		if (!article)
		{
			fclose(fp); DeleteBill(bill);
			return NULL;
		}

		InsertArticleSorted(&bill->articleHead, article); //sortirano unosi artikl u racun
	}

	fclose(fp);

	return bill;
}

int InsertBillSorted(BillPosition head, BillPosition bill) {

	BillPosition p = head;
	BillPosition added = bill;
	BillPosition previous = NULL;
	BillPosition last = head;

	while (p->next != NULL)
	{
		p = p->next;
		if (DateCompare(p->date, added->date) > 0)
		{
			previous = FindBefore(head, p);
			InsertBillAfter(previous, added);
			return EXIT_SUCCESS;
		}
	}

	while (last->next != NULL)
		last = last->next;

	InsertBillAfter(last, added);

	return EXIT_SUCCESS;
}

char* EnterFileName(void)
{
	char* str = NULL;
	str = malloc(sizeof(char) * 30);
	printf("\nUNESITE NAZIV DATOTEKE:\n\t> ");
	scanf(" %s", str);
	return str;
}

int ReenterFileName(BillPosition bP)
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
			if (ReadBillNamesFromFile(bP, fileName) == EXIT_SUCCESS)
			{
				return EXIT_SUCCESS;
				break;
			}
		}
	}
	return EXIT_SUCCESS;
}

int PrintBills(BillPosition head) {

	BillPosition current = head->next;

	while (current != NULL)
	{
		PrintBillContent(current);
		current = current->next;
	}

	return EXIT_SUCCESS;
}

int PrintBillContent(BillPosition bill) {

	ArticlePosition current = bill->articleHead->next;

	printf("\tDATUM\n\t\t> ");
	PrintDate(bill->date);
	printf("\tPROIZVODI [naziv kolicina cijena]:\n");

	while (current != NULL)
	{
		PrintArticle(current);
		printf("\r\n");
	}

	return EXIT_SUCCESS;
}

int DeleteAllBills(BillPosition head) {

	while (head->next != NULL)
		DeleteBillAfter(head);

	return EXIT_SUCCESS;
}

int DeleteBillAfter(BillPosition current) {

	BillPosition deleting = current->next;

	if (!deleting)
		return EXIT_SUCCESS;

	current->next = deleting->next;
	DeleteBill(deleting);

	return EXIT_SUCCESS;
}

int DeleteBill(BillPosition bill) {

	if (!bill)
		return EXIT_SUCCESS;

	if (bill->date)
		free(bill->date);

	DeleteAllBills(&bill->articleHead);
	free(bill);
}