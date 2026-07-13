#include<stdio.h>
#include<stdlib.h>
#include<time.h>
int count = 0;
void maxmin(int a[], int i, int j, int *max, int *min)
{
    int max1, min1;
    if(i==j)
    {
        *max=a[i];
        *min=a[i];
    }
    else if(i==j-1)
    {
        count++;
        if(a[i]>a[j])
        {
            *max=a[i];
            *min=a[j];
        }
        else
        {
            *max=a[j];
            *min=a[i];
        }
    }
    else
    {
        int mid=(i+j)/2;
        maxmin(a, i, mid, max, min);
        maxmin(a, mid+1, j, &max1, &min1);
        count+=2;
        if(max1>*max)
            *max=max1;
        if(min1<*min)
            *min=min1;
        
    }
}
int main()
{
    srand(time(0));
    int n;
    printf("Enter the number of elements: ");
    scanf("%d", &n);
    int* a = malloc(n*sizeof(*a));
    
    for(int i=0; i<n; i++)
        a[i]=rand()%90 + 10;
    for(int i=0; i<n; i++)
        printf("%d ", a[i]);
    int max, min;
    maxmin(a, 0, n-1, &max, &min);
    printf("\nMaximum element: %d\n", max);
    printf("Minimum element: %d\n", min);
    printf("Number of comparisons: %d\n", count);
    return 0;
}