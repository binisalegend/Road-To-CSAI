#include<bits/stdc++.h>
using namespace std;
#define MAX_SIZE 2000005

void swap(vector<int> &nums, int i, int j) 
{
    int temp = nums[i];
    nums[i] = nums[j];
    nums[j] = temp;
}

/* 选取三个元素的中位数 */
int medianThree(vector<int> &nums, int left, int mid, int right) 
{
    // 此处使用异或运算来简化代码
    // 异或规则为 0 ^ 0 = 1 ^ 1 = 0, 0 ^ 1 = 1 ^ 0 = 1
    if ((nums[left] < nums[mid]) ^ (nums[left] < nums[right]))
        return left;
    else if ((nums[mid] < nums[left]) ^ (nums[mid] < nums[right]))
        return mid;
    else
        return right;
}

/* 哨兵划分（三数取中值） */
int partition(vector<int> &nums, int left, int right) 
{
    // 选取三个候选元素的中位数
    int med = medianThree(nums, left, (left + right) / 2, right);
    // 将中位数交换至数组最左端
    swap(nums, left, med);
    // 以 nums[left] 作为基准数
    int i = left, j = right;
    while (i < j) 
    {
        while (i < j && nums[j] >= nums[left])
            j--; // 从右向左找首个小于基准数的元素
        while (i < j && nums[i] <= nums[left])
            i++;          // 从左向右找首个大于基准数的元素
        swap(nums, i, j); // 交换这两个元素
    }
    swap(nums, i, left); // 将基准数交换至两子数组的分界线
    return i;            // 返回基准数的索引
}

/* 快速排序 */
void quickSort(vector<int> &nums, int left, int right) {
    // 子数组长度为 1 时终止递归
    if (left >= right)
        return;
    // 哨兵划分
    int pivot = partition(nums, left, right);
    // 递归左子数组、右子数组
    quickSort(nums, left, pivot - 1);
    quickSort(nums, pivot + 1, right);
}


int main()
{
    vector<int> Y_location;
    int a, b;
    while (scanf("%d,%d\n", &a, &b) != EOF)
        Y_location.push_back(b);
    quickSort(Y_location, 0, Y_location.size() - 1);
    if (Y_location.size() % 2 == 0)
        cout << Y_location[Y_location.size() / 2 - 1] << endl;
    else
        cout << Y_location[Y_location.size() / 2] << endl;
    return 0;
}