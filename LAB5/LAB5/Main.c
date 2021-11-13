#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Functions.h"

int main(int argc, char** argv)
{
	Element stack = {.next = NULL, .number = 0.0};
	Position s1 = &stack;

	char* fileName = NULL;
	int odabir = 0;

	printf("\t\tPROGRAM ZA RACUNANJE POSTFIKSA IZ DATOTEKE:\n\n");

	fileName = EnterFileName();

	if (ReadFile(s1, fileName) == EXIT_FAILURE) 
		ReenterFileName(s1); //ukoliko datoteka nije ucitana

	return EXIT_SUCCESS;
}