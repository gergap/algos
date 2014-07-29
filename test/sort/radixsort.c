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
#include <sort/radixsort.h>

void test_radixsort(void);
void register_tests(void);

/* this test sort pure arrays of ints,
 * so the key is the value itself.
 */
static int key(const void *val)
{
    const int *v = val;
    return *v;
}

/* simple test */
void test_radixsort(void)
{
    int list[] = { 17, 23, 1, 12, 59, 44, 103, 5, 6, 7, 8, 1023, 32700 };
    int expected[] = { 1, 5, 6, 7, 8, 12, 17, 23, 44, 59, 103, 1023, 32700 };
    size_t size = sizeof(int);
    size_t num = sizeof(list) / size;

    radixsort(list, num, size, key);
    UCOMPAREMEM((const unsigned char*)list, sizeof(list), (const unsigned char*)expected, sizeof(expected));
}

void register_tests(void)
{
    UREGISTER_NAME("sort/radixort");
    UREGISTER_TEST(test_radixsort);
}

UTEST_MAIN()

