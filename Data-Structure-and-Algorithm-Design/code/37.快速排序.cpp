#include<bits/stdc++.h>
using namespace std;

const int cutoff = 5;
vector<int> median3;

void InsertionSort(vector<int>& nums, int left, int right) 
{
    for (int i = left + 1; i <= right; ++i) 
    {
        int key = nums[i];
        int j = i - 1;
        while (j >= left && nums[j] > key) 
        {
            nums[j + 1] = nums[j];
            --j;
        }
        nums[j + 1] = key;
    }
}

int Median3(vector<int>& nums, int left, int right) 
{
    if (right - left < 2) 
    {
        return -1;
    }

    int center = (left + right) / 2;
    if (nums[left] > nums[center]) swap(nums[left], nums[center]);
    if (nums[left] > nums[right]) swap(nums[left], nums[right]);
    if (nums[center] > nums[right]) swap(nums[center], nums[right]);

    swap(nums[center], nums[right - 1]);
    median3.push_back(nums[right - 1]);
    return nums[right - 1];
}

void QuickSort(vector<int>& nums, int left, int right) 
{
    if (left + cutoff <= right) 
    {
        int pivot = Median3(nums, left, right);
        if (pivot == -1) return;

        int i = left, j = right - 1;
        for (;;) 
        {
            while (nums[++i] < pivot) {}
            while (nums[--j] > pivot) {}
            if (i < j)
                swap(nums[i], nums[j]);
            else
                break;
        }
        swap(nums[i], nums[right - 1]);
        QuickSort(nums, left, i - 1);
        QuickSort(nums, i + 1, right);
    } 
    else 
    {
        InsertionSort(nums, left, right);
    }
}

int main() 
{
    vector<int> nums;
    int num;
    char ch;
    while (scanf("%d%c", &num, &ch) == 2 && ch != '#') 
    {
        nums.push_back(num);
    }
    QuickSort(nums, 0, nums.size() - 1);

    printf("After Sorting:\n");
    for (int i = 0; i < nums.size(); ++i) 
    {
        printf("%d ", nums[i]);
    }
    printf("\n");

    printf("Median3 Value:\n");

    if (median3.size() == 0) printf("none\n");
    else 
    {
        for (int i = 0; i < median3.size(); ++i) 
        {
            printf("%d ", median3[i]);
        }
        printf("\n");
    }
    return 0;
}