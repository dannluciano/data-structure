#include <stdlib.h>
#include <assert.h>
#include "date.h"

bool date_is_valid(date_t date)
{
    if (date.month < 1 || date.month > 12)
    {
        return false;
    }
    if (date.month == 4 || date.month == 6 || date.month == 9 || date.month == 11)
    {
        return date.day > 0 && date.day <= 30;
    }
    if (date.month == 1 || date.month == 3 || date.month == 5 || date.month == 7 || date.month == 8 || date.month == 10 || date.month == 12)
    {
        return date.day > 0 && date.day <= 31;
    }
    if (date.month == 2)
    {
        if ((date.year % 4 == 0 && date.year % 100 != 0) || (date.year % 400 == 0))
        {
            return date.day > 0 && date.day <= 29;
        }
        return date.day > 0 && date.day <= 28;
    }
    return false;
}

bool date_parse(const char *str, date_t *date)
{
    if (strlen(str) != 10)
    {
        return false;
    }
    if (str[2] != '/' && str[5] != '/')
    {
        return false;
    }

    char daystr[3] = {str[0], str[1], '\0'};

    char monthstr[3] = {str[3], str[4], '\0'};

    char yearstr[5] = {str[6], str[7], str[8], str[9], '\0'};

    date->day = atoi(daystr);
    date->month = atoi(monthstr);
    date->year = atoi(yearstr);

    return date_is_valid(*date);
}

int main(int argc, char const *argv[])
{
    assert(date_is_valid((date_t){.day = 1, .month = 1, .year = 1970}) == true);
    assert(date_is_valid((date_t){.day = 1, .month = 1, .year = 2000}) == true);
    assert(date_is_valid((date_t){.day = 30, .month = 4, .year = 2024}) == true);
    assert(date_is_valid((date_t){.day = 31, .month = 7, .year = 2024}) == true);
    assert(date_is_valid((date_t){.day = 29, .month = 2, .year = 2020}) == true);

    assert(date_is_valid((date_t){.day = 32, .month = 1, .year = 1970}) == false);
    assert(date_is_valid((date_t){.day = 31, .month = 4, .year = 2024}) == false);
    assert(date_is_valid((date_t){.day = 29, .month = 2, .year = 2019}) == false);
    assert(date_is_valid((date_t){.day = 0, .month = 1, .year = 2024}) == false);
    assert(date_is_valid((date_t){.day = 15, .month = 13, .year = 2024}) == false);
    assert(date_is_valid((date_t){.day = 31, .month = 2, .year = 2020}) == false);

    assert(date_is_valid((date_t){.day = 29, .month = 2, .year = 2000}) == true);
    assert(date_is_valid((date_t){.day = 29, .month = 2, .year = 1900}) == false);
    assert(date_is_valid((date_t){.day = 29, .month = 2, .year = 1996}) == true);
    assert(date_is_valid((date_t){.day = 29, .month = 2, .year = 2004}) == true);
    assert(date_is_valid((date_t){.day = 29, .month = 2, .year = 2024}) == true);
    assert(date_is_valid((date_t){.day = 29, .month = 2, .year = 2032}) == true);

    assert(date_is_valid((date_t){.day = 29, .month = 2, .year = 1600}) == true);
    assert(date_is_valid((date_t){.day = 29, .month = 2, .year = 2000}) == true);
    assert(date_is_valid((date_t){.day = 29, .month = 2, .year = 2400}) == true);

    assert(date_is_valid((date_t){.day = 29, .month = 2, .year = 1999}) == false);
    assert(date_is_valid((date_t){.day = 29, .month = 2, .year = 2023}) == false);
    assert(date_is_valid((date_t){.day = 29, .month = 2, .year = 2101}) == false);

    assert(date_is_valid((date_t){.day = 29, .month = 2, .year = 1700}) == false);
    assert(date_is_valid((date_t){.day = 29, .month = 2, .year = 1800}) == false);
    assert(date_is_valid((date_t){.day = 29, .month = 2, .year = 1900}) == false);
    assert(date_is_valid((date_t){.day = 29, .month = 2, .year = 2100}) == false);

    date_t new_date = {.day = 0, .month = 0, .year = 0};
    assert(date_parse("01/01/1970", &new_date) == true);
    assert(date_parse("29/02/2400", &new_date) == true);
    assert(date_parse("29/02/2100", &new_date) == false);

    return EXIT_SUCCESS;
}
