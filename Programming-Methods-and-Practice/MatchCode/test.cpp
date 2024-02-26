#include<bits/stdc++.h>
using namespace std;
    
#define MAXLENGTH 100000

int String_length, operation_num;    
char str[MAXLENGTH] = "";
char order[129] = {0};

int main()
{
    cin >> String_length >> operation_num;
    cin >> str;

    getchar();
    for (int i = 0; i <= 128; i++)
    {
        order[i] = i;
    }

    while (operation_num--)
    {
        char ch1, ch2;
        cin >> ch1 >> ch2;
        int loc1 = -1, loc2 = -1;

        for (int i = 33; i < 127; i++)
        {
            if (order[i] == ch1)
            {
                loc1 = i;
            }
            if (order[i] == ch2)
            {
                loc2 = i;
            }
            if (loc1 != -1 && loc2 != -1)
            {
                break;
            }
        }
        order[loc1] = ch2;
        order[loc2] = ch1;
    }

    for (int i = 0; i < String_length; i++)
    {
        str[i] = order[str[i]];
    }

    cout << str << endl;
    system("pause");
    return 0;
}