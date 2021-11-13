#ifndef FUNCTIONS_H
#define FUNCTIONS_H
#define MAX_SIZE (50)
#define MAX_LENGTH (1024)

struct _Element;

typedef struct _Element* Position;

typedef struct _Element
{
	double number;
	Position next;

} Element;

char* EnterFileName(void); //korisnikov unos imena datoteke
Position CreateElement(double number); //unos procitanog broja u listu
int PushElement(Position head, double number); //unos broja na vrh stoga
int DeleteAfter(Position position); //brisanje nakon odredjenog clana
int PopElement(double* value, Position head); //brisanje elementa na vrhu stoga
int CalculatePostfix(Position head, char operation); //racunanje postfiksa
int ReadLine(Position head, char* buffer); //citanje retka
int ReadFile(Position head, char* fileName); //ucitavanje postfiksa iz datoteke
int PrintOperation(double op1, double op2, double result, char operation); //ispisivanje operacije
int DeallocateStack(Position head); //brisanje svih elemenata
int ReenterFileName(Position head); //ukoliko korisnik zeli pokusati upisati drugi naziv datoteke

#endif

