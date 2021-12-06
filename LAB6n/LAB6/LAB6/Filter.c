#define _CRT_SECURE_NO_WARNINGS

#include "Filter.h"

#include <stdio.h>
#include <stdlib.h>

int InitializeFilter(FilterPosition filter) {

    filter->from = NULL;
    filter->to = NULL;
    memset(filter->name, MAX_ARTICLE_NAME, 0);

    return EXIT_SUCCESS;
}

FilterPosition CreateFilterToFromDate(char* DateFromStr, char* DateToStr, char* ArticleName) {

    FilterPosition filter = NULL;

    filter = (FilterPosition)malloc(sizeof(Filter));

    if (!filter)
    {
        system("Color C"); perror("Pogreska pri alokaciji filtera. . .\n");
        return NULL;
    }

    InitializeFilter(filter);

    filter->from = CreateDate(DateFromStr);

    if (!filter->from)
    {
        DeleteFilter(filter);
        return NULL;
    }

    filter->to = CreateDate(DateToStr);

    if (!filter->to)
    {
        DeleteFilter(filter);
        return NULL;
    }

    strcpy(filter->name, ArticleName);

    return filter;
}

int DeleteFilter(FilterPosition filter) {

    if (filter->from)
    {
        free(filter->from);
    }

    if (filter->to)
    {
        free(filter->to);
    }

    free(filter);

    return EXIT_SUCCESS;
}

int UserSearchArticleInRange(BillPosition head) {

    char article[MAX_ARTICLE_NAME] = { 0 };
    char DateFrom[MAX_DATE_AS_STRING] = { 0 };
    char DateTo[MAX_DATE_AS_STRING] = { 0 };

    FilterPosition filter = NULL;

    system("Color B");  printf("\tPRETRAGA\n");
    printf("\t [proizvod] [datum od] [datum do]\n");

    do {
        printf("\tVAS ODABIR > ");
        scanf(" %s %s %s", article, DateFrom, DateTo);

        filter = CreateFilterToFromDate(DateFrom, DateTo, article);
    } while (!filter);

    SearchArticleInRange(head, filter);
    DeleteFilter(filter);

    return EXIT_SUCCESS;
}

int SearchArticleInRange(BillPosition head, FilterPosition filter) {

    int TotalCount = 0;
    float TotalPrice = 0.0f;

    BillPosition bill = NULL;

    printf("\nFILTER:\n");

    for (bill = head->next; bill != NULL; bill = bill->next) 
    {
        if (IsDateInsideOfRange(bill->date, filter->from, filter->to)) 
        {
            ArticlePosition article = FindArticleByName(&bill->articleHead, filter->name);

            if (article) 
            {
                printf("\t\t- ");
                PrintArticle(article);
                puts("");
                TotalCount += article->count;
                TotalPrice += article->count * article->price;
            }
        }
    }

    printf( "\tNAZIV: \"%s\"\r\n" "\t\t\tKOLICINA:\t\t%d\r\n" "\t\t\tUKUPNA ZARADA\t%.02f\r\n", filter->name, TotalCount, TotalPrice);
}