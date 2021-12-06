#ifndef BILL_H
#define BILL_H
#include "Date.h"
#include "Article.h"

#define MAX_BILL_NAME (128)

struct _bill;

typedef struct _bill* BillPosition;

typedef struct _bill {
    char name[MAX_BILL_NAME];
    DatePosition date;
    ArticlePosition articleHead;
    BillPosition next;
} Bill;

int InitializeBill(BillPosition bP); //postavljanje svih vrij. na 0
BillPosition FindBefore(BillPosition head, BillPosition current); //pronalaz prethodnika
int InsertBillAfter(BillPosition current, BillPosition added); //unos nakon
int ReadBillNamesFromFile(BillPosition head, char* fileName); //ucitavanje prve datoteke
BillPosition ReadBillData(BillPosition head, char* billName); //citanje pojedinog racuna
int InsertBillSorted(BillPosition head, BillPosition bill); //sortirani unos racuna
char* EnterFileName(void); //unos naziva datoteke
int ReenterFileName(BillPosition bP); //ponovni unos imena datoteke
int PrintBills(BillPosition head);// ispis svih racuna
int PrintBillContent(BillPosition bill); //ispis sadrzaja racuna
int DeleteAllBills(BillPosition head); //oslobadjanje svih racuna
int DeleteBillAfter(BillPosition current); //brisi racun iza pozicije
int DeleteBill(BillPosition bill); //izbrisi jedan racun


#endif