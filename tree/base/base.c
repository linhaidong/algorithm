/*************************************************************************
    > File Name: base.c
    > Author:     linhaidong
    > Mail:       linhaidong@alibaba-inc.com 
    > Time:      2018年08月09日 星期四 16时37分35秒
    > Abstract: 
 ************************************************************************/
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

int charg_leaf(int node, int size)
{
    if(size == 1 || size == 0)
        return 1;
    //if (size == 2)
    if(node <= (size/2-1))
        return 0;
    else
        return 1;
}

int main()
{
    printf("(0,3)%d\r\n", charg_leaf(0,3));
    printf("(1,3)%d\r\n", charg_leaf(1,3));
    printf("(2,3)%d\r\n", charg_leaf(2,3));


    
    printf("(0,5)%d\r\n", charg_leaf(0,5));
    printf("(1,5)%d\r\n", charg_leaf(1,5));
    printf("(2,5)%d\r\n", charg_leaf(2,5));
    printf("(3,5)%d\r\n", charg_leaf(3,5));
    printf("(4,5)%d\r\n", charg_leaf(4,5));

    return 0;
}
