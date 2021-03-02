#pragma once
#include <stdlib.h>
#include <string.h>

static const double* sortdata = NULL; /* used in the quicksort algorithm */

//*******************
static int
compare_index(const void* a, const void* b)
/* Helper function for sort. Previously, this was a nested function under
 * sort, which is not allowed under ANSI C.
 */
{
    const int i1 = *(const int*)a;
    const int i2 = *(const int*)b;
    const double term1 = sortdata[i1];
    const double term2 = sortdata[i2];

    if (term1 < term2) return -1;
    if (term1 > term2) return +1;
    return 0;
}


void
cluster_sort_index(int n, const double data[], int index[])
/* Sets up an index table given the data, such that data[index[]] is in
 * increasing order. Sorting is done on the indices; the array data
 * is unchanged.
 */
{
    int i;

    sortdata = data;
    for (i = 0; i < n; i++) index[i] = i;
    qsort(index, n, sizeof(int), compare_index);
}

