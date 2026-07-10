#include <stdio.h>
#include <stdlib.h>
#include <time.h>
void swap(int *a, int *b)
{
    int temp = *a;
    *a = *b;
    *b = temp;
}

/* Heapify function (for Max Heap) */
void heapify(int arr[], int n, int i)
{
    int largest = i;        // assume root is largest
    int left = 2*i + 1;     // left child
    int right = 2*i + 2;    // right child

    if(left < n && arr[left] > arr[largest])
        largest = left;

    if(right < n && arr[right] > arr[largest])
        largest = right;

    if(largest != i)
    {
        swap(&arr[i], &arr[largest]);

        // Recursively heapify affected subtree
        heapify(arr, n, largest);
    }
}

/* Heap Sort function */
void heapSort(int arr[], int n)
{
    // Step 1: Build Max Heap
    for(int i = n/2 - 1; i >= 0; i--)
        heapify(arr, n, i);

    // Step 2: Extract elements from heap
    for(int i = n-1; i > 0; i--)
    {
        swap(&arr[0], &arr[i]);   // move root to end

        heapify(arr, i, 0);       // heapify reduced heap
    }
}

int main(){
    srand(time(0));
    int n;
    printf("Enter number of elements: ");
    scanf("%d",&n);
    int arr[n];
    for(int i=0;i<n;i++){
        arr[i]=10 + rand()%90;
    }
    printf("Array before sorting: ");
    for(int i=0;i<n;i++){
        printf("%d ",arr[i]);
    }
    heapSort(arr,n);
    printf("\nArray after sorting: ");
    for(int i=0;i<n;i++){
        printf("%d ",arr[i]);
    }
    return 0;
}