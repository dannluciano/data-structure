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

char *date_to_str(date_t *date)
{
    if (date->month < 1 || date->month > 12)
    {
        return NULL; // mês inválido
    }
    const char *month_dict[] = {
        "janeiro", "fevereiro", "março", "abril", "maio", "junho",
        "julho", "agosto", "setembro", "outubro", "novembro", "dezembro"};

    char *date_str = malloc(32);
    if (!date_str)
    {
        return NULL;
    }

    snprintf(date_str, 32, "%d de %s de %d", date->day, month_dict[date->month - 1], date->year);
    return date_str;
}