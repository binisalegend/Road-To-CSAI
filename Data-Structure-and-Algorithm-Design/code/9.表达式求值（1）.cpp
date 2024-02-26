#include<bits/stdc++.h>
using namespace std;
#define INT 2147483647
#define INT2 2147483646

int N, flag = 0, AfterCalculate = INT;   
char LastCharacter = ' ';
stack<char> Symbol;
stack<int> number;

bool isSymbol(char element) //判断是不是字符的函数
{
    if (element == '+' || element == '-' || element == '*' || element == '/' || element == '^' || element == '%' || element == ')' || element == '(')
    {
        return true;
    }
    return false;
}

bool isOperator(char element) //判断是不是运算符的函数
{
    if (element == '+' || element == '-' || element == '*' || element == '/' || element == '%' || element == '^' || element == '(')
    {
        return true;
    }
    return false;
}

int NumProcess(char &loc)  //处理输入数字的函数
{
    int num = loc - '0';
    LastCharacter = loc;
    loc = getchar();
    while (isdigit(loc))
    {
        num *= 10;
        num += loc - '0';
        LastCharacter = loc;
        loc = getchar();
    }
    return num;
}

int Calculate(int front, char op, int back)  //运算函数
{
    switch (op)
    {
        case '+':
            return front + back;
        case '-':
            return front - back;
        case '*':
            return front * back;
        case '/':
            if (back != 0)
            {
                return front / back;
            }
            else
            {
                printf("Divide 0.\n");
                break;
            }
        case '%':
            return front % back;
        case '^':
            if (back >= 0)
            {
                return pow(front, back);
            }
            else
            {
                printf("error.\n");
                break;
            }
        default:
            printf("error.\n");
            break;
    }
    return INT2;  //出现INT2表示是运算过程出错，即已经输出过报错了
}

void StackCalculate()
{
    int start = 0, end = 0, Flag = 0;
    if (!number.empty())
    {
        end = number.top();
        number.pop();
    }
    if (!number.empty())
    {
        start = number.top();
        number.pop();
        Flag = 1;
    }
    if (Flag == 1)
    {
        AfterCalculate = Calculate(start, Symbol.top(), end);
    }
}

int main()
{
    cin >> N;
    getchar();
    while (N--)   //读取有多少组数据
    {
        int except = 0;
        char loc;
        loc = getchar();
        while (loc != '\n')  //开始接收字符串
        {
            if (!isSymbol(loc)) //不是字符，开始读数
            {
                if (flag == 0)   //前面不是负号
                {
                    int num = NumProcess(loc);
                    number.push(num);
                    continue;
                }
                else  //前面被判定有负号，返回负值
                {
                    int num = -NumProcess(loc);
                    number.push(num);
                    flag = 0;
                    continue;
                }    
            }
            else  //接收到字符
            {
                if ((loc == '+' || loc == '*' || loc == '/' || loc == '%' || loc == '^' || loc == ')') && LastCharacter == '(')
                {
                    printf("error.\n");
                    except = 1;  //要用这个读取到错误后的垃圾字符
                    goto end;
                }
                if (loc == '-' && (isOperator(LastCharacter) || number.empty())) //接收到代表负号的‘-’号
                {
                    flag = 1; //用flag记录下存在负号，下一次读数生效
                }
                else if (loc == '-' || loc == '+')
                {
                    while (!Symbol.empty() && Symbol.top() != '(')
                    {
                        StackCalculate();
                        if (AfterCalculate != INT && AfterCalculate != INT2)
                        {
                            number.push(AfterCalculate);
                        }
                        else if (AfterCalculate == INT2)
                        {
                            goto end;
                        }
                        else
                        {
                            except = 2;
                            goto end2;
                        }
                        Symbol.pop();
                    }
                    Symbol.push(loc);
                }
                else if (loc == '*' || loc == '/' || loc == '%')
                {
                    if (!Symbol.empty())
                    {
                        while (Symbol.top() == '^' || Symbol.top() == '%' || Symbol.top() == '*' || Symbol.top() == '/')
                        {
                            StackCalculate();
                            if (AfterCalculate != INT && AfterCalculate != INT2)
                            {
                                number.push(AfterCalculate);
                            }
                            else if (AfterCalculate == INT2)
                            {
                                goto end;
                            }
                            else
                            {
                                except = 2;
                                goto end2;
                            }
                            Symbol.pop();
                            if (Symbol.empty())
                            {
                                break;
                            }
                        }
                    }
                    Symbol.push(loc);
                }
                else if (loc == '^' || loc == '(')
                {
                    Symbol.push(loc);
                }
                else if (loc == ')')
                {
                    if (!Symbol.empty())
                    {
                        while (Symbol.top() != '(')
                        {
                            StackCalculate();
                            if (AfterCalculate != INT && AfterCalculate != INT2)
                            {
                                number.push(AfterCalculate);
                            }
                            else if (AfterCalculate == INT2)
                            {
                                goto end;
                            }
                            else
                            {
                                except = 2;
                                goto end2;
                            }
                            Symbol.pop();
                            if (Symbol.empty())
                            {
                                printf("error.\n");
                                except = 1;
                                goto end;
                            }
                        }
                    }
                    Symbol.pop();
                }

                LastCharacter = loc;
                loc = getchar();
            }
        }

        while (!Symbol.empty() && number.size() >= 2)
        {
            StackCalculate();
            if (AfterCalculate != INT && AfterCalculate != INT2)
            {
                number.push(AfterCalculate);
            }
            else if (AfterCalculate == INT2)
            {
                goto end;
            }
            else
            {
                except = 2;
                goto end2;
            }
            Symbol.pop(); 
        }
        
        if (Symbol.empty() && number.size() == 1)
        {
            printf("%d\n", number.top());
        }
        else 
        {
            printf("error.\n");
        }

        end2:;
        if (except == 2)
        {
            printf("error.\n");
        }
        end:;
        if (except == 1)
        {
            loc = getchar();
            while (loc != '\n')
            {
                loc = getchar();
            }
        }
        while (!Symbol.empty())
        {
            Symbol.pop();
        }
        while (!number.empty())
        {
            number.pop();
        }
    }
    system("pause");
    return 0;
}