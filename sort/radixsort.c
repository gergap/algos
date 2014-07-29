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
#include "radixsort.h"
#include <string.h> /* for memcpy */
#include <malloc.h>
#include <stdlib.h>

/** swap marcro for abitrary sized data.
 * Compilers are smart enough to replace memcpy with move calls
 * if the data fits into a register.
 */
#define SWAP(a, b, size) ({char tmp[size]; memcpy(tmp, a, size); memcpy(a, b, size); memcpy(b, tmp, size);})

struct element {
    int *value;
    struct element *next;
};

void *xmalloc(size_t size);
void *xmalloc(size_t size)
{
    void *ret = malloc(size);
    if (ret == NULL) exit(EXIT_FAILURE);
    return ret;
}

/** Radixsort algorithm.
 * Sorts an array with \c num elements of size \c size.
 * The \c base arguments points to the start of the array.
 *
 * This algorithm is faster then typical algorithms.
 * Generic sort algorithm which work with comparison
 * operate in O(n*logn). Radixsort works in O(n),
 * but assumes that the key is an integer
 * (at least this implementation).
 *
 * The function \c key returns the key for a given element.
 *
 */
void radixsort(void *base, size_t num, size_t size,
               int (*key)(const void *))
{
    size_t i;
    int j;
    size_t pos;
    int k, idx, shift = 0, rounds = sizeof(int);
    struct element *first[256] = { NULL };
    struct element *last[256] = { NULL };
    struct element *e;

    /* with 256 buckets and 32bit ints we need 4 rounds: 256^4 = 2^32
     * with only 16 buckets we could do it in 8 rounds: 16^8 = 2^32
     */
    for (j = 0; j < rounds; j++) {
        pos = (size_t)base;
        for (i = 0; i < num; i++, pos += size) {
            k = key((void*)pos) >> shift;
            idx = k & 0xff;
            e = xmalloc(sizeof(*e));
            e->value = xmalloc(size);
            e->next = NULL;
            memcpy(e->value, (void*)pos, size);
            if (last[idx] == NULL) {
                /* create new list at idx */
                first[idx] = last[idx] = e;
            } else {
                /* append at list end */
                last[idx]->next = e;
                last[idx] = e;
            }
        }
        pos = (size_t)base;
        for (i = 0; i < 256; i++) {
            last[i] = NULL;
            /* iterate over list if exists */
            while ((e = first[i]) != NULL) {
                memcpy((void*)pos, e->value, size);
                pos += size;
                first[i] = e->next;
                free(e->value);
                free(e);
            }
        }
        shift += 8;
    }
}
