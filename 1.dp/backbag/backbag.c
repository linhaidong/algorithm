/*************************************************************************
    > File Name: backbag.c
    > Author: ma6174
    > Mail: ma6174@163.com 
    > Created Time: 2016年07月11日 星期一 19时22分27秒
 ************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
void print_array(int *max_val, int num , int max_wight )
{
    int i, j;
    printf("begin:\r\n");
    for(i = 0; i <= num; i++)
    {
        for(j = 0; j <= max_wight; j++)
        {
            printf("%3d ", *(max_val+i*max_wight+j+i));
        }
        printf("\r\n");
    }
}
int operate(int wight[],  int val[], int num, int max_wight)
{
    int i, j;
    int max_val[num+1][max_wight+1];
    memset(max_val, 0, (max_wight+1)*(num+1)*4);
    print_array((int *)max_val, num, max_wight);
    for(i = 1; i <= num; i++)
    {
        //分别计算每行，即每个数据依次插入，获取最大值
        for(j = 1; j <=  max_wight; j++)
        {
            //当前物体重量，大于总重量，则选用原来的最优
            //竖向赋值，i-1, j不变
            if( wight[i-1] > j)
            {
                max_val[i][j] = max_val[i-1][j];
                continue;
            }
            //竖向比较（上面为未装入物品），比较最优解
            //装入物品的价值大于不装入物品的价值
            if((max_val[i-1][j - wight[i-1]] + val[i-1]) > max_val[i][j-1])
                max_val[i][j] = max_val[i-1][j - wight[i-1]] + val[i-1];
            else //不装入物品，比较不装入和装入的最大值
                max_val[i][j] = max_val[i][j-1] > max_val[i-1][j] ? max_val[i][j-1]:max_val[i-1][j];
        }
        print_array((int *)max_val, num, max_wight);
    }
    print_array((int *)max_val, num, max_wight);
    return max_val[num][max_wight];
}
int main()
{
    int wight[3] = {3,4,5};
    int val[3]={4,5,6};
    printf("max is %d\r\n",  operate(wight, val, 3, 10));
    return 0;
}


