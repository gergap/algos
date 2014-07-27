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
#include "heapsort.h"
#include <string.h> /* for memcpy */
#include <assert.h>

/** swap marcro for abitrary sized data.
 * Compilers are smart enough to replace memcpy with move calls
 * if the data fits into a register.
 */
#define SWAP(a, b, size) ({char tmp[size]; memcpy(tmp, a, size); memcpy(a, b, size); memcpy(b, tmp, size);})

static void swap(void *base, int i, int j, size_t size)
{
    size_t a = (size_t)base + i * size;
    size_t b = (size_t)base + j * size;
    SWAP((void*)a, (void*)b, size);
}

static int greater(void *base, int i, int j, size_t size, int (*cmp)(const void *, const void *))
{
    size_t a = (size_t)base + i * size;
    size_t b = (size_t)base + j * size;
    return (cmp((void*)a, (void*)b) > 0);
}

static void reheap(void *base, int i, int k, size_t size, int (*cmp)(const void *, const void *))
{
    int j = i;
    int son;

    do {
        if (2 * j > k) {
            break;
        } else {
            if (2 * j + 1 <= k) {
                if (greater(base, 2*j-1, 2*j, size, cmp))
                    son = 2 * j;
                else
                    son = 2 * j + 1;
            } else {
                son = 2 * j;
            }
        }
        if (greater(base, son-1, j-1, size, cmp) ) {
            swap(base, j-1, son-1, size);
            j = son;
        } else {
            break;
        }
    } while (1);
}

void heapsort(void *base, size_t num, size_t size,
              int (*cmp)(const void *, const void *))
{
    int i;

    for (i = num / 2; i >= 1; i--) reheap(base, i, num, size, cmp);
    for (i = num; i >= 2; i--) {
        swap(base, 0, i-1, size);
        reheap(base, 1, i-1, size, cmp);
    }
}

