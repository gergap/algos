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
#include "mergesort.h"
#include <string.h> /* for memcpy */
#include <assert.h>

/** swap marcro for abitrary sized data.
 * Compilers are smart enough to replace memcpy with move calls
 * if the data fits into a register.
 */
#define SWAP(a, b, size) ({char tmp[size]; memcpy(tmp, a, size); memcpy(a, b, size); memcpy(b, tmp, size);})

void mergesort(void *base, size_t num, size_t size,
               int (*cmp)(const void *, const void *))
{

}

