#ifndef ARTICLE_H
#define ARTICLE_H

#define MAX_ARTICLE_NAME (128)

struct _article;

typedef struct _article* ArticlePosition;

typedef struct _article {
    char name[MAX_ARTICLE_NAME];
    int count;
    float price;
    ArticlePosition next;
} Article;

int InitializeArticle(ArticlePosition aP); //postavljanje na 0
ArticlePosition CreateArticle(char* line); //kreiranje artikla iz procitanog retka
int InsertArticle(ArticlePosition head, ArticlePosition article); //sortirani unos artikla
int InsertArticleAfter(ArticlePosition current, ArticlePosition added); //dodavanje nakon odredjenog elementa
int PrintArticle(ArticlePosition article); //ispis proizvoda
int DeleteAllArticles(ArticlePosition head); //oslobadjanje svih proizvoda
int DeleteArticleAfter(ArticlePosition current); //brise proizvod iza
int ArticleToString(char* placeholder, ArticlePosition article); //pretvaranje u string
ArticlePosition FindArticleByName(ArticlePosition head, char* name); //pretraga po imenu

#endif