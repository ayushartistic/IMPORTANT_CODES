#include <stdio.h>
#include <stdlib.h>
#include <time.h>
void swap(int *a, int *b)
{
    int temp = *a;
    *a = *b;
    *b = temp;
}

int Lpartition(int a[], int low, int high)
{
    int i = low - 1;
    int pivot = a[high];
    for (int j = low; j < high; j++)
    {
        if (a[j] <= pivot)
        {
            i++;
            swap(&a[i], &a[j]);
        }
    }
    swap(&a[i + 1], &a[high]);
    return i + 1;
}

int Hpartition(int a[], int low, int high)
{
    int pivot = a[low];   // choose first element as pivot
    int i = low - 1;
    int j = high + 1;

    while (1)
    {
        // move i right
        do {
            i++;
        } while (a[i] < pivot);

        // move j left
        do {
            j--;
        } while (a[j] > pivot);

        // stop condition
        if (i >= j)
            return j;

        // swap elements
        swap(&a[i], &a[j]);
    }
}
void quicksort(int a[], int low, int high)
{
    if (low < high)
    {
        int pi = Lpartition(a, low, high);
        quicksort(a, low, pi - 1);
        quicksort(a, pi + 1, high);
    }
}

void quicksortHoare(int a[], int low, int high)
{
    if (low < high)
    {
        int pi = Hpartition(a, low, high);
        quicksortHoare(a, low, pi);
        quicksortHoare(a, pi + 1, high);
    }
}
int main()
{
    srand(time(0));
    int n;
    printf("Enter no. of elements: ");
    scanf("%d", &n);
    int *a = malloc(n * sizeof(*a));

    for (int i = 0; i < n; i++)
        a[i] = rand() % 90 + 10;
    printf("Array before sorting: ");
    for (int i = 0; i < n; i++)
        printf("%d ", a[i]);
    quicksort(a, 0, n - 1);
    printf("\nArray after sorting: ");
    for (int i = 0; i < n; i++)
        printf("%d ", a[i]);

    for (int i = 0; i < n; i++)
        a[i] = rand() % 90 + 10;
    printf("\nArray before sorting: ");
    for (int i = 0; i < n; i++)
        printf("%d ", a[i]);
    quicksortHoare(a, 0, n - 1);
    printf("\nArray after sorting: ");
    for (int i = 0; i < n; i++)
        printf("%d ", a[i]);
    free(a);
    return 0;
}