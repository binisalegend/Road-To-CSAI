//这种做法的好处是不需要数组来记录每次游戏的结果，节省内存
#include<stdio.h>
#include<string.h>
int main()
{
   int Jerry_num = 1,min = 1, max = 10;
   char Tom_ans[1000] = ""; 
   int loc = 0;
   scanf("%d", &Jerry_num);
   while(Jerry_num != 0) 
   {
      if(Jerry_num >= 1 && Jerry_num <= 10) 
      {
         gets(Tom_ans);
      } 
      else
      {
         break;
      }
      if(strcmp(Tom_ans, "too low") == 0)
      {
         if (Jerry_num > min)
         {
            min = Jerry_num + 1;
         }
      } 
      else if(strcmp(Tom_ans, "too high") == 0)
      {
         if (Jerry_num < max)
         {
            max = Jerry_num - 1;
         }
      }
      else if(strcmp(Tom_ans, "right on") == 0)
      {
         if(Jerry_num > max || Jerry_num < min)
         {
            printf("Tom is dishonest\n");
            loc = 1;
         }
         else if (loc == 0)
         {
            printf("Tom may be honest\n");
         }
      }
      loc = 0, min = 1, max = 10;  //这个在每次结束后重新定义最大最小值差点把我玩死...
      scanf("%d", &Jerry_num);   //这句要放到循环末尾，因为0进入后没有Tom的回答
   }
   return 0;
}