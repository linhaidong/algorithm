/*************************************************************************
    > File Name: sort.c
    > Author:     linhaidong
    > Mail:       linhaidong@alibaba-inc.com 
    > Time:      2018年08月09日 星期四 18时50分45秒
    > Abstract: 
 ************************************************************************/
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

void print(int arr[], int len)
{
    int i;
    printf("array:");
    for(i=0; i<len; i++)
    {
        printf("%d, ",arr[i] );
    }
    printf("\r\n");
}
