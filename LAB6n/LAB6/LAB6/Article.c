#define _CRT_SECURE_NO_WARNINGS
#include "Article.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_ARTICLE_AS_STRING (1024)

int InitializeArticle(ArticlePosition aP) {

	aP->count = 0;
	memset(aP->name, 0, MAX_ARTICLE_NAME);
	aP->price = 0.0f;
	aP->next = NULL;

	return EXIT_SUCCESS;
}

ArticlePosition CreateArticle(char* line)
{
	ArticlePosition article = NULL;
	int format = 0;

	char store_name[MAX_ARTICLE_NAME] = { 0 };
	int store_count = 0;
	float store_price = 0.0f;

	if (!line)
	{
		system("color C"); printf("Nepravilno unesen string. . .\n");
		return NULL;
	}

	article = (ArticlePosition)malloc(sizeof(Article));

	if (!article)
	{
		system("color C"); perror("Ne moze se alocirati memorija!\n");
		return NULL;
	}

	InitializeArticle(article);

	format = sscanf(line, "%s %d %f", &article->name, &article->count, &article->price);

	if (format != 3)
	{
		system("color C"); printf("Nepravilno unesen format linije [NAZIV	KOLICINA	CIJENA]. . .\n");
		free(article);
		return NULL;
	}

	return article;
}

int InsertArticleSorted(ArticlePosition head, ArticlePosition article)
{
	ArticlePosition current = head;

	while (current->next != NULL && strcmp(current->next->name, article->name) < 0) {
		current = current->next;
	}

	InsertArticleAfter(current, article);

	return EXIT_SUCCESS;

}

int InsertArticleAfter(ArticlePosition current, ArticlePosition added)
{
	added->next = current->next;
	current->next = added;

	return EXIT_SUCCESS;
}

int ArticleToString(char* placeholder, ArticlePosition article) {

	if (!placeholder)
	{
		system("Color C"); printf("Uneseni string je prazan. . .\n");
		return -4;
	}

	sprintf(placeholder, "%s %d %.2f", article->name, article->count, article->price);
	return EXIT_SUCCESS;
}


int PrintArticle(ArticlePosition article) {

	char ArticleAsString[MAX_ARTICLE_AS_STRING] = { 0 };

	ArticleToString(ArticleAsString, article);
	printf(ArticleAsString);

	return EXIT_SUCCESS;
}

int DeleteAllArticles(ArticlePosition head) {

	while (head->next != NULL)
		DeleteArticleAfter(head);

	return EXIT_SUCCESS;
}

int DeleteArticleAfter(ArticlePosition current) {

	ArticlePosition deleting = current->next;

	if (!deleting)
		return EXIT_SUCCESS;

	current->next = deleting->next;
	free(deleting);

	return EXIT_SUCCESS;
}

ArticlePosition FindArticleByName(ArticlePosition head, char* name) {

	ArticlePosition article = head;

	while (article->next != NULL)
	{
		if (strcmp(article->name, name) == 0)
			return article;
		article = article->next;
	}

	return NULL;
}
