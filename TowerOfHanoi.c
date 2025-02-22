// tower of hanoi

#include <stdio.h>
#include<time.h>

void toh(int n, int from, int to, int via)
{
    if (n == 1)
    {
        printf("move plate 1 from %d to %d via %d\n", from, to, via);
        return;
    }
    toh(n - 1, from, via, to);
    printf("move plate %d from %d to %d via %d\n", n, from, to, via);
    toh(n - 1, via, to, from);
}

int main()
{
    int n;
    printf("Enter a number : ");
    scanf("%d", &n);
    if (n <= 0)
    {
        printf("INVALID INPUT\n");
        return 0;
    }
    clock_t start = clock();
    toh(n, 1, 3, 2);
    clock_t end = clock();
    double time_taken = ((double)(end - start)) / CLOCKS_PER_SEC;
    printf("Time taken to run the algorithm: %f seconds\n", time_taken);
    return 0;
}