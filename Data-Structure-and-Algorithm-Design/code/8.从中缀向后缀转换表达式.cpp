#include<bits/stdc++.h>
using namespace std;
    
int N; 
vector<char> prefix, postfix;
stack<char> location;

void convert()
{
    for (auto element : prefix)
    {
        if (element == '(' || element == '^') //如果左括号或者最高优先级运算符^就直接入栈
        {
            location.push(element);
        }
        else if (element == '*' || element == '/')  //乘除运算符优先级情况
        {
            if (!location.empty())
            {
                while (location.top() == '^' || location.top() == '*' || location.top() == '/')
                {
                    postfix.push_back(location.top());
                    location.pop();
                    if (location.empty())
                    {
                        break;
                    }
                }
            }
            location.push(element);
        }
        else if (element == '+' || element == '-')
        {
            while ((!location.empty()) && location.top() != '(')
            {
                postfix.push_back(location.top());
                location.pop();
            }
            location.push(element);
        }
        else if (element == ')')
        {
            while (location.top() != '(')
            {
                postfix.push_back(location.top());
                location.pop();
            }
            location.pop();
        }
        else
        {
            postfix.push_back(element);
        }
    }
    while (!location.empty())
    {
        postfix.push_back(location.top());
        location.pop();
    }
}

int main()
{
    char loc = ' ';
    cin >> N;
    while (N--)
    {
        int count = 0;
        while (1)
        {
            cin >> loc;
            if (loc != '#')
            {
                prefix.push_back(loc);
                if (loc != '(' && loc != ')')
                {
                    count++;
                }
            }
            else
            {
                break;
            }
        }
        convert();
        for (auto i : postfix)
        {
            cout << i;
        }
        cout << endl;
        postfix.clear();
        prefix.clear();
    }
    
    system("pause");
    return 0;
}