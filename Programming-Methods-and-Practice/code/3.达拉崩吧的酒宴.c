// 这题的思路我自己理解是先拿具体的数字来试，比如6、7这样的
// 然后在稍微大一点的数字试验时，可以发现最基本的思路就是两个中有一个有毒，另一个就是安全的
// 比如1-10，就可以1-4、3-6、5-8这样每两组()包括最后的9.10都有两个数的重合,就可以再加一组判断两个的
// 这样就可以联想到二进制的问题，即都转化为二进制，每一位为1的都由一只小白鼠试验
// 只要对应位数的小白鼠死了，就说明这只小白鼠对应的位数是1
// 这样，最终就是根据酒的桶数转化为二进制最大位数是多少，就需要几只小白鼠
// 划分依据为log2

#include<stdio.h>
#include<math.h>
int main()
{
    int Times, Mice_nums;
    long int Bucket_nums; 
    scanf("%d", &Times);
    for (int i = 0; i < Times; i++)
    {
        scanf("%ld", &Bucket_nums);
        Mice_nums = ceil(log2(Bucket_nums));
        printf("%d\n", Mice_nums);
    }
    return 0;
}