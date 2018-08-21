/*************************************************************************
    > File Name: count.c
    > Author:     linhaidong
    > Mail:       linhaidong@alibaba-inc.com 
    > Time:      2018年08月09日 星期四 18时28分41秒
    > Abstract: 
 ************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "sort.h"


/* --------------------------------------------------------------------------*/
/**
 * @Synopsis 计数排序 
    //统计个数
    //格式相加得到位置
    //写入临时数组
    //赋值到原数组
 * @Param a[]
 * @Param len
 *
 * @Returns   
 */
/* ----------------------------------------------------------------------------*/
int count_sort(int a[], int len)
{
    int cout[10] = {0};
    int i;

    //统计个数
    for(i =0 ;i < len; i++)
    {
        cout[a[i]]++;
    }
    print(cout, 10);
    //格式相加得到位置
    for(i = 1; i < 10; i++)
    {
        cout[i] = cout[i] + cout[i-1];
        printf("%d, ",cout[i]);
    }
    print(cout, 10);
    printf("\r\n");
    //写入临时数组
    int * temp = (int *)malloc(len);
    if (!temp)
        return -1;
    for (i = 0 ; i < len; i++)
    {
        //找到位置
        int t = cout[a[i]]--;
        temp[t-1] = a[i];
    }
    //赋值到原数组
    for(i = 0; i < len; i++)
    {
        a[i] = temp[i];
    }
    if(temp)
         free(temp);

}
int main()
{
    //int a[] = {5,4,9,8,7,6,3,2,1};
    //int a[] = {5,4,9,5,4,5};
    int a[] = {8,8,8,8,5,5,5,5,5,5};
    int len = sizeof(a)/sizeof(int);
    print(a, len);
    count_sort(a, len);
    print(a, len);
}
