#if !defined(DATE_H)
#define DATE_H

#include <stdbool.h>
#include <string.h>

typedef struct date_t
{
    unsigned day;
    unsigned month;
    unsigned year;
} date_t;

bool date_is_valid(date_t date);
bool date_parse(const char *str, date_t *date);

#endif // DATE_H
