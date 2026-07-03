#include <stdio.h>
#define max 10
int M[max][max], S[max][max];

void matrixChainMulti(int p[], int len)
{
    int n = len - 1;

    for(int i = 1; i <= n; i++)
    {
        M[i][i] = 0;
    }

    for(int l = 2; l <= n; l++)
    {
        for(int i = 1; i <= n - l + 1; i++)
        {
            int j = i + l - 1;

            M[i][j] = 9999;

            for(int k = i; k <= j - 1; k++)
            {
                int cost = M[i][k]
                         + M[k + 1][j]
                         + p[i - 1] * p[k] * p[j];

                if(cost < M[i][j])
                {
                    M[i][j] = cost;
                    S[i][j] = k;
                }
            }
        }
    }
}

void POP(int i, int j)
{
    if(i == j)
    {
        printf("A%d", i);
    }
    else
    {
        printf("(");

        POP(i, S[i][j]);
        POP(S[i][j] + 1, j);

        printf(")");
    }
}

void show(int n)
{
    printf("M Matrix\n");

    for(int i = 1; i <= n; i++)
    {
        for(int j = 1; j <= n; j++)
        {
            printf("%3d ", M[i][j]);
        }
        printf("\n");
    }

    printf("S Matrix\n");

    for(int i = 1; i <= n; i++)
    {
        for(int j = 1; j <= n; j++)
        {
            printf("%3d ", S[i][j]);
        }
        printf("\n");
    }
}

int main()
{
    int p[5] = {2, 3, 5, 2, 4};

    matrixChainMulti(p, 5);

    show(4);

    printf("\nOptimal Parenthesization: ");
    POP(1, 4);

    printf("\nMinimum Cost = %d\n", M[1][4]);

    return 0;
}