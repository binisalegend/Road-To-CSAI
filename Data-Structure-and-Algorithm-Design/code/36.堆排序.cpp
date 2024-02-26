#include<bits/stdc++.h>
using namespace std;

/* 堆的长度为 n ，从节点 i 开始，从顶至底堆化 */
void siftDown(vector<int> &nums, int n, int i) 
{
    while (true) 
    {
        // 判断节点 i, l, r 中值最大的节点，记为 ma
        int l = 2 * i + 1;
        int r = 2 * i + 2;
        int ma = i;
        if (l < n && nums[l] > nums[ma])
            ma = l;
        if (r < n && nums[r] > nums[ma])
            ma = r;
        // 若节点 i 最大或索引 l, r 越界，则无须继续堆化，跳出
        if (ma == i) 
        {
            break;
        }
        // 交换两节点
        swap(nums[i], nums[ma]);
        // 循环向下堆化
        i = ma;
    }
}

/* 堆排序 */
void heapSort(vector<int> &nums) 
{
    // 建堆操作：堆化除叶节点以外的其他所有节点
    for (int i = nums.size() / 2 - 1; i >= 0; --i) 
    {
        siftDown(nums, nums.size(), i);
    }
    // // 从堆中提取最大元素，循环 n-1 轮
    // for (int i = nums.size() - 1; i > 0; --i) 
    // {
    //     // 交换根节点与最右叶节点（即交换首元素与尾元素）
    //     swap(nums[0], nums[i]);
    //     // 以根节点为起点，从顶至底进行堆化
    //     siftDown(nums, i, 0);
    // }

}

int main()
{
    int NumOfNumber;
    scanf("%d",&NumOfNumber);
    vector<int> nums;

    for (int i = 0; i < NumOfNumber; ++i) 
    {
        int n;
        scanf("%d", &n);
        nums.push_back(n);
    }

    for (int i = 0; i < 3; i++)
    {
        heapSort(nums);
        for (int i = 0; i < NumOfNumber; ++i) 
        {
            printf("%d ", nums[i]);
        }
        cout << endl;
        nums[0] = nums[NumOfNumber-1];
        NumOfNumber--;
    }
    return 0;
}