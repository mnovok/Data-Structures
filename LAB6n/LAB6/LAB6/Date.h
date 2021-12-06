#ifndef DATE_H
#define DATE_H
#include <stdbool.h>

#define YEAR_STRING_LENGTH (4)           // 2021
#define DAY_STRING_LENGTH (2)            // 07
#define MONTH_STRING_LENGTH (2)          // 10
#define DASH_LENGTH (1)                  // -
#define NULL_TERMINATING_CHAR_LENGTH (1) // \0
#define MAX_DATE_AS_STRING (YEAR_STRING_LENGTH + DASH_LENGTH + MONTH_STRING_LENGTH + DASH_LENGTH + DAY_STRING_LENGTH + NULL_TERMINATING_CHAR_LENGTH)

struct _date;

typedef struct _date* DatePosition;

typedef struct _date {
    int year;
    int month;
    int day;
} Date;

DatePosition CreateDate(char* str); //stvaranje instance datuma
int DateCompare(DatePosition d1, DatePosition d2); //usporedba datuma
int PrintDate(DatePosition date); //ispis datuma
int DateToString(char* placeholder, DatePosition date); //pretvaranje datuma u string
bool IsDateInsideOfRange(DatePosition date, DatePosition from, DatePosition to); //istinitost uvjeta

#endif