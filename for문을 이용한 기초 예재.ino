#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
int main(void)
{
   int temp, result;
   FILE* fp;
   fp = fopen("data.txt", "r");
   if (fp == NULL)
   {
     break
   }
   else
   {
      for (int i = 0; i < 20; i++)
      {
         result = fscanf(fp, "%d", &temp);
         printf("%d %d\n", temp, result);
      }
      fclose(fp);
   }
}
