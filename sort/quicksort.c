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
#include "quicksort.h"
#include <string.h> /* for memcpy */
#include <assert.h>

/*#define DEBUG*/
#ifdef DEBUG
# include <stdio.h>
# define DEBUGPRINT(fmt, ...) printf(fmt, ##__VA_ARGS__)
static void printlist(int list[], size_t num)
{
    size_t i;

    printf("%i", list[0]);
    for (i = 1; i < num; i++) {
        printf(" %i", list[i]);
    }
    printf("\n");
}
#else
# define DEBUGPRINT(fmt, ...)
# define printlist(a, b)
#endif

/** swap marcro for abitrary sized data.
 * Compilers are smart enough to replace memcpy with move calls
 * if the data fits into a register.
 */
#define swap(a, b, size) ({char tmp[size]; memcpy(tmp, a, size); memcpy(a, b, size); memcpy(b, tmp, size);})

/** Quicksort algorithm.
 * Sorts an array with \c num elements of size \c size.
 * The \c base arguments points to the start of the array.
 *
 * The  ontents of the array are sorted in ascending order according to a
 * comparison function pointed to by compar, which is called with two arguments
 * that point to the objects being compared.
 *
 * The comparison function must return an integer less than, equal to, or
 * greater than zero if the first argument is considered to be respectively
 * less than, equal to, or greater than the second. If two members compare as
 * equal, their order in the sorted array is undefined.
 */
void quicksort(void *base, size_t num, size_t size,
               int (*cmp)(const void *, const void *))
{
    char *b = base;
    char *left = base;
    char *right = (char *)base + (num - 1) * size;
    char *pivot;
    size_t index;

    DEBUGPRINT("Sorting: ");
    printlist(base, num);

    if (num < 2)
        return; /* nothing to sort */

    if (num == 2) {
        /* just swap the elements if necessary */
        if ((*cmp)(right, left) < 0) {
            swap(left, right, size);
        }
        DEBUGPRINT("Sorted: ");
        printlist(base, num);
        return;
    }

    /* choose a pivot element. We choose the median of the leftmost, middle and rightmost value. */
    pivot = b + (num / 2) * size;
    if ((*cmp)(pivot, left) < 0)
        swap(left, pivot, size);
    if ((*cmp)(right, pivot) < 0) {
        swap(pivot, right, size);
        /* we need to check again if now left is smaller than the middle value. */
        if ((*cmp)(pivot, left) < 0)
            swap(left, pivot, size);
    }

    DEBUGPRINT("Swapped: ");
    printlist(base, num);
    DEBUGPRINT("pivot=%i\n", *((int *)pivot));

    if (num == 3) {
        /* choosing the pivot has already sorted these three elements */
        DEBUGPRINT("Sorted: ");
        printlist(base, num);
        return;
    }

    /* partition */
    while (left < right) {
        while ((*cmp)(left, pivot) < 0)
            left += size;
        while (!((*cmp)(right, pivot) < 0))
            right -= size;

        if (left < right) {
            swap(left, right, size);
            DEBUGPRINT("Swapped: ");
            printlist(base, num);
            /* if we have swapped the pivot element we must update the pivot pointer */
            if (left == pivot)
                pivot = right;
            else if (right == pivot)
                pivot = left;
            left += size;
            right -= size;
        } else {
            /* we are done */
            break;
        }
    }
    DEBUGPRINT("Sorted: ");
    printlist(base, num);

    /* left is now right+1*size, because no value can <piv and >=piv.
     * example:
     * index: 0  1  2  3  4  5  6  7
     * data:  5 12  1 23 17 44 103 59
     *              ^  ^  ^
     *              r  l  p
     * all values from 0-r ara < p
     * all values from l-(n-1) are >= p
     */
    index = (left - b) / size;
    DEBUGPRINT("index=%lu\n", index);
    assert(index > 0 && index < num);
    quicksort(b, index, size, cmp);
    quicksort(b + index * size, num - index, size, cmp);
}

