/*
 *  Copyright (C) 2014 Gerhard Gappmeier <gappy1502@gmx.net>
 *
 *  This file is part of Calgos.
 *
 *  Calgos is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  Calgos is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with Calgos. If not, see <http://www.gnu.org/licenses/>.
 */
#include <testlib.h>
#include <malloc.h>
#include <string.h>
#include <sort/quicksort.h>

void test_quicksort(void);
void test_1million(void);
void register_tests(void);
void test(void);

static int compare_int(const void *a, const void *b)
{
    const int *ia = a;
    const int *ib = b;
    if (*ia < *ib) return -1;
    if (*ia > *ib) return 1;
    return 0;
}

/* simple test */
void test_quicksort(void)
{
    int list[] = { 17, 23, 1, 12, 59, 44, 103, 5, 6, 7, 8 };
    int expected[] = { 1, 5, 6, 7, 8, 12, 17, 23, 44, 59, 103 };
    size_t size = sizeof(int);
    size_t num = sizeof(list) / size;

    quicksort(list, num, size, compare_int);
    UCOMPAREMEM((const unsigned char*)list, sizeof(list), (const unsigned char*)expected, sizeof(expected));
}

void test_1million(void)
{
    int i;

    #define NUM 1000000
    int *data = malloc(NUM*sizeof(int));
    UVERIFY(data != NULL);

    /* use constant seed to have reproduceable results */
    srand(0);
    for (i = 0; i< NUM; i++) {
        data[i] = rand();
    }

    UBENCHMARK {
        quicksort(data, NUM, sizeof(int), compare_int);
    }

    free(data);
}

void test(void)
{
    char data[20] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20 };
    char tmp;

    tmp = data[0];
    memmove(data, data+1, 19);
    data[19] = tmp;

    memmove(data+1, data, 19);
    data[0] = tmp;

}

void register_tests(void)
{
    UREGISTER_NAME("sort/quicksort");
    UREGISTER_TEST(test);
    UREGISTER_TEST(test_quicksort);
    UREGISTER_TEST(test_1million);
}

UTEST_MAIN()

