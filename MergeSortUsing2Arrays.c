// merge sort using 2 arrays

#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<time.h>
#include<limits.h>

void merge(double* arr, int p, int q, int r)
{
    int n1=q-p+1;
    int n2=r-q;
    double* left = (double*)malloc((n1+1)*sizeof(double));
    double* right = (double*)malloc((n2+2)*sizeof(double));

    int i,j,k;

    for(i=0;i<n1;i++)
    {
        left[i]=arr[p+i];
    }
    for(j=0;j<n2;j++)
    {
        right[j]=arr[q+j+1];
    }
    left[i]=INFINITY;
    right[j]=INFINITY;
    i=0;
    j=0;

    for(k=p;k<=r;k++)
    {
        if(left[i]<=right[j])
        {
            arr[k]=left[i];
            i=i+1;
        }
        else
        {
            arr[k]=right[j];
            j++;
        }
    }
}

void mergesort(double* arr, int p, int r)
{
    if(p<r)
    {
        int q = p+((r-p)/2);
        mergesort(arr,p,q);
        mergesort(arr,q+1,r);
        merge(arr,p,q,r);
    }
}

int main()
{
	int n, i;
	printf("Enter array size : ");
	scanf("%d", &n);
	double *arr = (double *)malloc(n * sizeof(double));
	if (arr == NULL)
	{
		printf("Error in creation\n");
		return 0;
	}
	for (i = 0; i < n; i++)
	{
		scanf("%lf", &arr[i]);
	}
	printf("Display before sorting : ");
	for (i = 0; i < n; i++)
	{
		printf("%lf ", arr[i]);
	}
	printf("\n");
	clock_t start = clock();
	mergesort(arr, 0, n - 1);
	clock_t end = clock();
	double time_taken = ((double)(end - start)) / CLOCKS_PER_SEC;
	printf("Display after sorting : ");
	for (i = 0; i < n; i++)
	{
		printf("%lf ", arr[i]);
	}
	printf("\n");

	printf("Time taken to run the algorithm: %f seconds\n", time_taken);
	return 0;
}
