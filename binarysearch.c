#include<stdio.h>
#include<stdlib.h>
#include<time.h>
int binarysearch(int arr[], int low, int high, int target){
    if(low>high) return -1;
    int mid = low+(high-low)/2;
    if(arr[mid]==target) return mid;
    else if(arr[mid]<target) return binarysearch(arr,mid+1,high,target);
    else return binarysearch(arr,low,mid-1,target);
}
void swap(int* a, int* b){
    int c = *a;
    *a = *b;
    *b = c;
}
void bubblesort(int arr[],int n){
    for(int i=0;i<n-1;i++){
        for(int j=0;j<n-i-1;j++){
            if(arr[j]>arr[j+1]) swap(&arr[j],&arr[j+1]);
        }
    }
}
int main(){
    srand(time(0));
    printf("Enter size of array: ");
    int n;
    scanf("%d",&n);
    int arr[n];
    for(int i=0;i<n;i++){
        arr[i] = rand()%90 + 10;
    }
    for(int i=0;i<n;i++){
        printf("%d ",arr[i]);
    }
    printf("\nAfter sorting: \n");
    bubblesort(arr,n);
    for(int i=0;i<n;i++){
        printf("%d ",arr[i]);
    }
    while(1){
        int x;
        printf("\nEnter target: ");
        scanf("%d",&x);
        int idx = binarysearch(arr,0,n-1,x);
        if(idx!=-1) printf("\nFound at %d\n",idx);
        else printf("\nNot found\n");
    }
    
}