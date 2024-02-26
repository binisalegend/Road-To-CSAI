#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<string.h>

int n;
long long int *loc;

long long int Merge(long long int *a, long long int *b, int left, int mid, int right)
{
    // printf("%d %d %d\n", left, mid, right);
    int l = left, r = mid + 1, tem = left;
    long long count = 0;
    while (l <= mid && r <= right)
    {
        if (a[l] <= a[r])
        {
            b[tem] = a[l];
            tem++;
            l++;
        }
        else
        {
            b[tem] = a[r];
            tem++;
            r++;
            count += r - tem;
        }
    }
    while (l <= mid)
    {
        b[tem] = a[l];
        tem++;
        l++;
    }
    while (r <= right)
    {
        b[tem] = a[r];
        tem++;
        r++;
    }
    for (int i = left; i <= right; i++)
    {
        a[i] = b[i];
    }
    return count;    
}

long long int MergeSort(long long int *a, int left, int right)
{
    long long int count = 0;
    if (left < right)
    {
        int middle = (left + right) / 2;
        // printf("%d\n", count);
        count += MergeSort(a, left, middle);
        count += MergeSort(a, middle + 1, right);
        count += Merge(a, loc, left, middle, right);
    }
    return count;
}


int main()
{
    scanf("%d", &n);
    loc = (long long int *)malloc((n + 1) * sizeof(long long int));

    long long int *height = (long long int *)malloc((n + 1) * sizeof(long long int));
    for (int i = 0; i < n; i++)
    {
        scanf("%lld", height + i);
    }

    long long int final_print = MergeSort(height, 0, n - 1);
    printf("%lld\n", final_print);
    return 0;
}