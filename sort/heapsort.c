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
#define swap(a, b, size) ({char tmp[size]; memcpy(tmp, a, size); memcpy(a, b, size); memcpy(b, tmp, size);})

/* for heapsort we use a heap which is implemented as an array.
 * the left child, right child and parent indeces in one based arrays are computed
 * this way:
 * left(i) = 2i
 * right(i) = 2i+1
 * parent(i) = i/2
 * Because in C we use zero based arrays we must slightly modfiy these formulas to:
 * left(i) = 2i+1
 * right(i) = 2i+2
 * parent(i) = (i+1)/2
 */

static int left(int i)
{
    return 2 * i + 1;
}

static int right(int i)
{
    return 2 * i + 2;
}

static int parent(int i)
{
    return (i + 1) / 2;
}

void heapsort(void *base, size_t num, size_t size,
              int (*cmp)(const void *, const void *))
{

}

