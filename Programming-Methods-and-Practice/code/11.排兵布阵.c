#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>

int numbers = 0;
long long int total_distance = 0, final_x = 0, final_y = 0;

typedef struct 
{
    long long int x;
    long long int y;
}solider;

//计算两位置间的曼哈顿距离
long long int Manhattan(solider a, long long int x, long long int y)
{
    return fabs(a.x - x) + fabs(a.y - y);
}

//为qsort函数准备的排序函数
int cmpx( const void *a ,const void *b)  
{  
    return ((*(solider *)a)).x - ((*(solider *)b)).x;
}
int cmpy( const void *a ,const void *b)  
{  
    return ((*(solider *)a)).y - ((*(solider *)b)).y;
}

int main()
{
    scanf("%d", &numbers);
    solider *loc = (solider *)malloc((numbers + 1) * sizeof(solider));
    for (int i = 0; i < numbers; i++)
    {
        scanf("%lld %lld", &loc[i].x, &loc[i].y);
    }

    //求出纵坐标目标值
    qsort(loc, numbers, sizeof(loc[0]), cmpy);

    final_y = loc[numbers / 2].y;
    
    qsort(loc, numbers, sizeof(loc[0]), cmpx);
    solider *help = (solider *)malloc((numbers + 1) * sizeof(solider));
    for (int i = 0; i < numbers; i++)
    {
        help[i].x = loc[i].x - i;
        help[i].y = loc[i].y;
    }
    
    qsort(help, numbers, sizeof(help[0]), cmpx);

    final_x = help[numbers / 2].x;

    for (int i = 0; i < numbers; i++)
    {
        total_distance += Manhattan(help[i], final_x, final_y);
        // printf("%lld\n", total_distance);
    }
    
    printf("%lld\n", total_distance);
    return 0;
}