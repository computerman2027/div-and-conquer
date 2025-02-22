#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int partition(int *arr, int p, int r)
{
    int x = arr[r];
    int i = p - 1;
    int j, temp;
    for (j = p; j < r; j++)
    {
        if (arr[j] <= x)
        {
            i = i + 1;
            temp = arr[i];
            arr[i] = arr[j];
            arr[j] = temp;
        }
    }
    temp = arr[i + 1];
    arr[i + 1] = arr[r];
    arr[r] = temp;
    return i + 1;
}

int randomizedPartition(int* arr, int p, int r)
{
    int x =p+ rand()%(r-p+1);
    int temp=arr[r];
    arr[r]=arr[x];
    arr[x]=temp;
    return partition(arr,p,r);
}

void randomizedquicksort(int *arr, int p, int r)
{
    if (p < r)
    {
        int q = randomizedPartition(arr, p, r);
        randomizedquicksort(arr, p, q - 1);
        randomizedquicksort(arr, q + 1, r);
    }
}
int main()
{
    srand(time(NULL));
    int n, i;
    printf("Enter array size : ");
    scanf("%d", &n);
    int *arr = (int *)malloc(n * sizeof(int));
    if (arr == NULL)
    {
        printf("Error in creation\n");
        return 0;
    }
    for (i = 0; i < n; i++)
    {
        scanf("%d", &arr[i]);
    }
    printf("Display before sorting : ");
    for (i = 0; i < n; i++)
    {
        printf("%d ", arr[i]);
    }
    printf("\n");
    clock_t start = clock();
    randomizedquicksort(arr, 0, n - 1);
    clock_t end = clock();
    double time_taken = ((double)(end - start)) / CLOCKS_PER_SEC;
    printf("Display after sorting : ");
    for (i = 0; i < n; i++)
    {
        printf("%d ", arr[i]);
    }
    printf("\n");

    printf("Time taken to run the algorithm: %f seconds\n", time_taken);
    return 0;
}
