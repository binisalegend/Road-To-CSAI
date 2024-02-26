#include<bits/stdc++.h> 
using namespace std;  
struct node{  
    //他之前连续大于他不在栈里面的木板数  
    int numBefore;  
    //位置  
    int i;  
    //高度  
    long long height;  
}arr[200000];  
  
long long n;  
long long res;  
  
  
int main()  
{  
    while(scanf("%lld", &n))  
    {  
        if (n == 0) 
        {  
            break;  
        }  
        stack <node> stk;  
  
        res= 0;  
        //input  
        for(int i = 0; i < n; i++)  
        {  
            cin >> arr[i].height;  
            arr[i].numBefore = 0;
            arr[i].i = i;  
        }  
          
        for(int i = 0; i < n; i++)  
        {  
            while(!stk.empty() && arr[i].height < stk.top().height)  
            {  
                node temp = stk.top();  
                //删除栈顶  
                stk.pop();  
                //更新  
                arr[i].numBefore += temp.numBefore + 1;  
                res = max(res, temp.height * (temp.numBefore + i - temp.i));  
            }  
            stk.push(arr[i]);  
        }  
          
        //计算站内最大面积  
        while(!stk.empty())  
        {  
            node temp = stk.top();  
            stk.pop();  
            if (temp.height * (temp.numBefore + n - temp.i) > res) 
            {  
                res = temp.height * (temp.numBefore + n - temp.i );  
            }  
        }
        cout << res << endl;  
    }  
    return 0;  
}