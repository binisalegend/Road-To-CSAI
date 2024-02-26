#include<stdio.h>
#include<stdlib.h>
#include<math.h>
typedef struct
{
    long int start;
    long int end;
}locate;

int cmp( const void *a ,const void *b)  
{  
    return ((*(locate*)a)).end - ((*(locate *)b)).end;
}

int main()
{
    int n, count = 1;
    scanf("%d", &n);
    
    locate *loc = (locate *)malloc(n * sizeof(locate));

    for (int i = 0; i < n; i++)
    {
        scanf("%ld %ld", &loc[i].start, &loc[i].end);
    }

    qsort(loc, n, sizeof(loc[0]), cmp);

    int second = 0, first = 0;
    for (second = 1; second < n; second++)
    {
        if (loc[second].start >= loc[first].end) 
        {
            count++;
            first = second;
        }
    }
    printf("%d\n", count);
    return 0;
}
