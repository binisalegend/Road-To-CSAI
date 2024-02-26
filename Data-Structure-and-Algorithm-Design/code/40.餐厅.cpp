#include<iostream>
using namespace std;

int main()
{
    int person_max = 0, person_min = 0, person_num, test_num = 0;
    char in_ch;

    scanf("%d", &test_num);
    getchar();

    while (test_num--)
    {
        person_num = 0;
        person_max = 0;
        person_min = 0;
        while (in_ch = getchar())
        {
            if (in_ch == '\n')
                break;
            if (in_ch == '+')
            {
                person_num++;
                if (person_num > person_max)
                    person_max = person_num;
            }
            else if (in_ch == '-')
            {
                person_num--;   
                if (person_num < person_min)
                    person_min = person_num;
            }
        }
        printf("%d\n", person_max-person_min);
    }

    return 0;
}