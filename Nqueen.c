#include <stdio.h>
#include <stdlib.h>
#define MAX 100

int n;
int queen[MAX];   // queen[row] = column

int isSafe(int row, int col)
{
    int i;

    for(i = 0; i < row; i++)
    {
        // Same column
        if(queen[i] == col)
            return 0;

        // Same diagonal
        if(abs(queen[i] - col) == abs(i - row))
            return 0;
    }

    return 1;
}

void printSolution()
{
    int i;

    for(i = 0; i < n; i++)
        printf("%d ", queen[i]);

    printf("\n");
}

void solve(int row)
{
    int col;

    if(row == n)
    {
        printSolution();
        return;
    }

    for(col = 0; col < n; col++)
    {
        if(isSafe(row, col))
        {
            queen[row] = col;
            solve(row + 1);
        }
    }
}

int main()
{
    printf("Enter N: ");
    scanf("%d", &n);

    solve(0);

    return 0;
}