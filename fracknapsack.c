#include<stdio.h>

int main()
{
    int n;
    float w;

    printf("Enter number of items: ");
    scanf("%d", &n);

    if(n <= 0)
    {
        printf("Invalid number of items\n");
        return 1;
    }

    printf("Enter capacity of knapsack: ");
    scanf("%f", &w);

    if(w <= 0)
    {
        printf("Invalid capacity\n");
        return 1;
    }

    float weight[n], profit[n], ratio[n];

    for(int i=0; i<n; i++)
    {
        printf("Enter weight and profit of item %d: ", i+1);
        scanf("%f %f", &weight[i], &profit[i]);

        if(weight[i] <= 0)
        {
            printf("Weight must be positive\n");
            return 1;
        }

        ratio[i] = profit[i] / weight[i];
    }

    for(int i=0; i<n-1; i++)
    {
        for(int j=0; j<n-i-1; j++)
        {
            if(ratio[j] < ratio[j+1])
            {
                float temp;

                temp = ratio[j];
                ratio[j] = ratio[j+1];
                ratio[j+1] = temp;

                temp = weight[j];
                weight[j] = weight[j+1];
                weight[j+1] = temp;

                temp = profit[j];
                profit[j] = profit[j+1];
                profit[j+1] = temp;
            }
        }
    }

    float total_profit = 0;

    for(int i=0; i<n; i++)
    {
        if(weight[i] <= w)
        {
            total_profit += profit[i];
            w -= weight[i];
        }
        else
        {
            total_profit += ratio[i] * w;
            break;
        }
    }

    printf("Maximum Profit = %.2f\n", total_profit);

    return 0;
}