#define _CRT_SECURE_NO_WARNINGS

#include "Date.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

DatePosition CreateDate(char* str) {

	DatePosition date = NULL;
	int format = 0; //uvjet 3 integera YYYY-MM-DD

	if (!str)
	{
		system("color C"); printf("Nepravilno unesen string. . .\n");
		return NULL;
	}

	date = (DatePosition)malloc(sizeof(Date));

	if (!date)
	{
		system("color C"); perror("Ne moze se alocirati memorija!\n");
		return NULL;
	}

	format = sscanf(str, "%d-%d-%d", &date->year, &date->month, &date->day);

	if (format != 3)
	{
		system("color C");
		printf("Nepravilno unesen format datuma [YYYY-MM-DD]. . .\n");
		free(date);
		return NULL;
	}

	return date;
}

int DateCompare(DatePosition d1, DatePosition d2)
{
	int result = d1->year - d2->year;

	if (result == 0) {
		result = d1->month - d2->month;

		if (result == 0) {
			result = d1->day - d2->day;
		}
	}
	return result;
}

int PrintDate(DatePosition date) {

	char DateAsString[MAX_DATE_AS_STRING] = { 0 };

	DateToString(DateAsString, date);
	printf(DateAsString);

	return EXIT_SUCCESS;
}

int DateToString(char* placeholder, DatePosition date) {

	if (!placeholder)
	{
		system("Color C"); printf("Uneseni string je prazan. . .\n");
		return -4;
	}

	if (!date)
	{
		sprintf(placeholder, "-");
		return EXIT_SUCCESS;
	}

	sprintf(placeholder, "%04d-%02d-%02d", date->year, date->month, date->day);
	return EXIT_SUCCESS;
}

bool IsDateInsideOfRange(DatePosition date, DatePosition from, DatePosition to) {

	return DateCompare(date, from) >= 0 && DateCompare(date, to) <= 0;
}