#ifndef FILTER_H
#define FILTER_H

#include "Date.h"
#include "Article.h"
#include "Bill.h"

struct _filter;

typedef struct _filter* FilterPosition;

typedef struct _filter {
    DatePosition from;
    DatePosition to;
    char name[MAX_ARTICLE_NAME];
} Filter;

int InitializeFilter(FilterPosition filter); //postavlja sve vrij. na 0
FilterPosition CreateFilterToFromDate(char* DateFromStr, char* DateToStr, char* ArticleName); //stvaranje filtera pretrazivanja po datumima
int DeleteFilter(FilterPosition filter); //brisanje filtera
int UserSearchArticleInRange(BillPosition head); //korisnikov unos
int SearchArticleInRange(BillPosition head, FilterPosition filter); //pretraga

#endif