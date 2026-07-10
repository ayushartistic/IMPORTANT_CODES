#include<stdio.h>
#include<stdlib.h>
#include<time.h>



void merge(int arr[], int aux[], int low, int mid, int high) {
    int i = low;      // left subarray pointer
    int j = mid + 1;  // right subarray pointer
    int k = low;      // merged array pointer

    while (i <= mid && j <= high) {
        // Stability ensured here
        if (arr[i] <= arr[j]) {
            aux[k++] = arr[i++];
        } else {
            aux[k++] = arr[j++];
        }
    }

    while (i <= mid) {
        aux[k++] = arr[i++];
    }

    while (j <= high) {
        aux[k++] = arr[j++];
    }

    // Copy back to original array
    for (i = low; i <= high; i++) {
        arr[i] = aux[i];
    }
}

void mergesort(int arr[], int aux[], int low, int high) {
    if (low >= high) return;

    int mid = low + (high - low) / 2;

    mergesort(arr, aux, low, mid);
    mergesort(arr, aux, mid + 1, high);

    // Optional optimization: skip merge if already sorted
    if (arr[mid] <= arr[mid + 1]) return;

    merge(arr, aux, low, mid, high);
}



int main(){
    srand(time(0));
    int n;
    printf("Enter number of elements: ");
    scanf("%d",&n);
    int arr[n];
    int *aux = (int *)malloc(n * sizeof(int));
    if (!aux) return 0; // handle allocation failure
    for(int i=0;i<n;i++){
        arr[i]=10 + rand()%90;
    }
    printf("Original array: ");
    for(int i=0;i<n;i++){
        printf("%d ",arr[i]);
    }
    printf("\n");
    mergesort(arr, aux, 0, n - 1);
    printf("Sorted array: ");
    for(int i=0;i<n;i++){
        printf("%d ",arr[i]);
    }
    printf("\n");
    free(aux);
    return 0;
}