#include<stdio.h>
int main()
{
    long long int length_max, height_max, count = 0, location, height = 0;
    scanf("%lld %lld", &length_max, &height_max);
    long long int height_last = height_max;

    scanf("%lld", &height);   //先在循环外读取第一个数赋给location
    location = height;
    for (long long int length = 1; length < length_max; length++)
    {
        scanf("%lld", &height);
        if (height <= location)
        {
           location = height;
        }
        else
        {
            count += height - location;
            location = height;
        }   
    }
    if (height_last > location)
    {
        count += height_last - location;
    }
    printf("%lld\n", count);
    return 0;
}

// //这种做法会超时，感觉是for循环嵌套导致时间复杂度较高导致的
// #include<stdio.h>
// #include<stdlib.h>
// int main()
// {
//     long int length_max, height_max, count = 0;
//     scanf("%ld %ld", &length_max, &height_max);
//     long int *height;
//     height = (long int *)malloc((length_max+1) * sizeof(long int));
//     for (int length = 0; length < length_max; length++)
//     {
//         scanf("%ld", &height[length]);
//     }
//     height[length_max] = height_max;
//     for (long int height_now = height_max; height_now > 0; height_now--)
//     {
//         for (long int i = 0; i < length_max; i++)
//         {
//             if (height[i] < height_now)
//             {
//                 if (height[i+1] >= height_now)
//                 {
//                     count++;
//                     i++;
//                 }
//                 else
//                 {
//                     continue;
//                 }    
//             }
//         }
//     }
//     printf("%ld\n", count);
//     return 0;
// }

