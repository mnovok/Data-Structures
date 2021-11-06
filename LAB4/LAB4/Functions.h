#ifndef FUNCTIONS_H
#define FUNCTIONS_H
#define MAX_SIZE (50)
#define MAX_LENGTH (1024)

struct _Polynomial;

typedef struct _Polynomial* Position;

typedef struct _Polynomial
{
	int koef;
	int pot;
	Position next;

} Polynomial;

char* EnterFileName(void); //korisnikov unos imena datoteke
Position CreatePolynomial(int coef, int exp); //kreiranje polinoma
int InsertAfter(Position position, Position newPolynomial); //dodavanje iza elementa
int InsertSorted(Position head, Position newPolynomial); //sortirani unos polinoma
int PrintList(Position first); //ispisuje cijelu listu
int ReadLine(Position head, char* buffer); //citanje retka
int ReadFile(Position head1, Position head2, char* fileName); //citanje dvaju polinoma iz datoteke
int DeleteNull(Position head); //brisanje novonastalog clana s koef. 0
int AddPolynomials(Position head1, Position head2, Position headS); //zbrajanje polinoma
int MultiplyPolynomials(Position head1, Position head2, Position headP); //mnozenje polinoma
int DeallocateList(Position head); //brisanje memorije

#endif