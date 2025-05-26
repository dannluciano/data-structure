#include <assert.h>
#include <stdlib.h>
#include <stdio.h>

#include "date.h"

void test(bool boolean_expression)
{
    assert(boolean_expression);
    putchar('.');
}

int main(int argc, char const *argv[])
{
    test(date_is_valid((date_t){.day = 1, .month = 1, .year = 1970}) == true);
    test(date_is_valid((date_t){.day = 1, .month = 1, .year = 1970}) == true);
    test(date_is_valid((date_t){.day = 1, .month = 1, .year = 2000}) == true);
    test(date_is_valid((date_t){.day = 30, .month = 4, .year = 2024}) == true);
    test(date_is_valid((date_t){.day = 31, .month = 7, .year = 2024}) == true);
    test(date_is_valid((date_t){.day = 29, .month = 2, .year = 2020}) == true);
    test(date_is_valid((date_t){.day = 32, .month = 1, .year = 1970}) == false);
    test(date_is_valid((date_t){.day = 31, .month = 4, .year = 2024}) == false);
    test(date_is_valid((date_t){.day = 29, .month = 2, .year = 2019}) == false);
    test(date_is_valid((date_t){.day = 0, .month = 1, .year = 2024}) == false);
    test(date_is_valid((date_t){.day = 15, .month = 13, .year = 2024}) == false);
    test(date_is_valid((date_t){.day = 31, .month = 2, .year = 2020}) == false);
    test(date_is_valid((date_t){.day = 29, .month = 2, .year = 2000}) == true);
    test(date_is_valid((date_t){.day = 29, .month = 2, .year = 1900}) == false);
    test(date_is_valid((date_t){.day = 29, .month = 2, .year = 1996}) == true);
    test(date_is_valid((date_t){.day = 29, .month = 2, .year = 2004}) == true);
    test(date_is_valid((date_t){.day = 29, .month = 2, .year = 2024}) == true);
    test(date_is_valid((date_t){.day = 29, .month = 2, .year = 2032}) == true);
    test(date_is_valid((date_t){.day = 29, .month = 2, .year = 1600}) == true);
    test(date_is_valid((date_t){.day = 29, .month = 2, .year = 2000}) == true);
    test(date_is_valid((date_t){.day = 29, .month = 2, .year = 2400}) == true);
    test(date_is_valid((date_t){.day = 29, .month = 2, .year = 1999}) == false);
    test(date_is_valid((date_t){.day = 29, .month = 2, .year = 2023}) == false);
    test(date_is_valid((date_t){.day = 29, .month = 2, .year = 2101}) == false);
    test(date_is_valid((date_t){.day = 29, .month = 2, .year = 1700}) == false);
    test(date_is_valid((date_t){.day = 29, .month = 2, .year = 1800}) == false);
    test(date_is_valid((date_t){.day = 29, .month = 2, .year = 1900}) == false);
    test(date_is_valid((date_t){.day = 29, .month = 2, .year = 2100}) == false);

    date_t new_date = {.day = 0, .month = 0, .year = 0};
    test(date_parse("01/01/1970", &new_date) == true);
    test(date_parse("29/02/2400", &new_date) == true);
    test(date_parse("29/02/2100", &new_date) == false);

    putchar('\n');
    return EXIT_SUCCESS;
}