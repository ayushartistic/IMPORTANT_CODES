#include<stdio.h>

typedef struct
{
    int id;
    int profit;
    int deadline;
} Job;

void swap(Job *a, Job *b)
{
    Job temp = *a;
    *a = *b;
    *b = temp;
}

int main()
{
    int n;

    printf("Enter the number of jobs: ");
    scanf("%d", &n);

    Job jobs[n];

    for(int i = 0; i < n; i++)
    {
        printf("Enter job id, profit and deadline for job %d: ", i + 1);
        scanf("%d %d %d", &jobs[i].id, &jobs[i].profit, &jobs[i].deadline);
    }

    for(int i = 0; i < n - 1; i++)
    {
        for(int j = 0; j < n - i - 1; j++)
        {
            if(jobs[j].profit < jobs[j + 1].profit)
            {
                swap(&jobs[j], &jobs[j + 1]);
            }
        }
    }

    int maxDeadline = 0;

    for(int i = 0; i < n; i++)
    {
        if(jobs[i].deadline > maxDeadline)
        {
            maxDeadline = jobs[i].deadline;
        }
    }

    int slot[maxDeadline + 1];

    for(int i = 0; i <= maxDeadline; i++)
    {
        slot[i] = -1;
    }

    int totalProfit = 0;

    printf("\nScheduled Jobs:\n");

    for(int i = 0; i < n; i++)
    {
        for(int j = jobs[i].deadline; j > 0; j--)
        {
            if(slot[j] == -1)
            {
                slot[j] = i;
                totalProfit += jobs[i].profit;
                break;
            }
        }
    }
    for(int i = 1; i <= maxDeadline; i++)
    {
        if(slot[i] != -1)
        {
            printf("Time Slot %d -> Job %d (Profit = %d)\n",
                   i,
                   jobs[slot[i]].id,
                   jobs[slot[i]].profit);
        }
    }

    printf("\nTotal Profit = %d\n", totalProfit);

    return 0;
}