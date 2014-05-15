#include <sort/quicksort.h>
#include <stdio.h>

#define UNUSED(x) (void)(x)

static int g_cnt = 0;

static int compare_int(const void *a, const void *b)
{
    const int *ia = a;
    const int *ib = b;
    g_cnt++;
    return ((*ia)-(*ib));
}

static void printlist(int list[], size_t num)
{
    size_t i;

    printf("%i", list[0]);
    for (i=1; i<num; i++) {
        printf(" %i", list[i]);
    }
    printf("\n");
}

int main(int argc, char *argv[])
{
    UNUSED(argc);
    UNUSED(argv);
    int list[] = { 17, 23, 1, 12, 59, 44, 103, 5, 6, 7, 8 };
    size_t size = sizeof(int);
    size_t num = sizeof(list) / size;

    printlist(list, num);
    //qsort(list, num, size, compare);
    quicksort(list, num, size, compare_int);
    printlist(list, num);
    printf("compare was called %i times.\n", g_cnt);

    return 0;
}
