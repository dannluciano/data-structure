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

    return EXIT_SUCCESS;
}
