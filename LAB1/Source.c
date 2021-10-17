#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <malloc.h>

#define MAX_SIZE (128)
#define MAX_LINE (1024)

typedef struct _student
{
	char ime[MAX_SIZE];
	char prezime[MAX_SIZE];
	double bodovi;

} student;

char* UnesiNazivDatoteke(void);
int ProcitajBrojRedaka(char*);
student* AlocirajMemorijuProcitajStudenta(int, char*);
int MaxBrBodova(int, student*);
int IspisStudenata(int, student*, int);



int main()
{

	char* naziv = NULL;
	int n = 0;
	int max_bodovi = 0;


	naziv = UnesiNazivDatoteke();
	n = ProcitajBrojRedaka(naziv);
	student* student = AlocirajMemorijuProcitajStudenta(n, naziv);
	max_bodovi = MaxBrBodova(n, student);
	IspisStudenata(n, student, max_bodovi);

	return 0;
}

char* UnesiNazivDatoteke()
{
	char* str = NULL;
	str = malloc(sizeof(char) * 20);
	printf("Unesite naziv datoteke:\n");
	scanf("%s", str);
	return str;
}

int ProcitajBrojRedaka(char* nazivDatoteke)
{
	int brojac = 0;
	FILE* fp = NULL;
	char buffer[MAX_LINE] = { 0 };

	fp = fopen(nazivDatoteke, "r");

	if (!fp)
	{
		printf("Pogreska pri ucitavanju datoteke!\n");
		return -1;
	}

	while (!feof(fp))
	{
		fgets(buffer, MAX_LINE, fp);
		brojac++;
	}

	fclose(fp);

	return brojac;

}

student* AlocirajMemorijuProcitajStudenta(int brojStudenata, char* nazivDatoteke)
{
	int brojac = 0;
	FILE* fp = NULL;
	student* studenti = NULL;

	studenti = (student*)malloc(brojStudenata * sizeof(student));

	fp = fopen(nazivDatoteke, "r");

	if (!fp)
	{
		printf("Pogreska pri alociranju memorije!\n");
		free(studenti);
		return NULL;
	}

	while (getc(fp) != '\n')
		continue;

	while (!feof(fp))
	{
		fscanf(fp, " %s %s %lf", studenti[brojac].ime, studenti[brojac].prezime, &studenti[brojac].bodovi);
		brojac++;
	}

	fclose(fp);

	return studenti;
}

int MaxBrBodova(int brojStudenata, student* student)
{
	int brojac = 0;
	int max_bodovi = student[0].bodovi;

	for (brojac = 1; brojac < brojStudenata; brojac++)
	{
		if (student[brojac].bodovi > max_bodovi)
			max_bodovi = student[brojac].bodovi;
	}

	return max_bodovi;

}

int IspisStudenata(int brojStudenata, student* student, int max)
{
	int brojac = 0;

	printf("\tIME\tPREZIME\tAPS.BOD\tREL.BOD\n");
	printf("\t~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");

	for (brojac = 0; brojac < brojStudenata; brojac++)
	{
		float relativan_broj_bodova = 0;
		relativan_broj_bodova = (float)student[brojac].bodovi / max * 100;
		printf("\t%s\t%s\t%.2f\t%.2f\n", student[brojac].ime, student[brojac].prezime, student[brojac].bodovi, relativan_broj_bodova);
	}

	return brojac;

}