/*************************************************************************
    > File Name: main.c
    > Author: linengier
    > Mail: linengier@126.com 
    > Created Time: 2016年09月27日 星期二 08时04分28秒
 ************************************************************************/
#include<stdio.h>
#include "avl.h"
int main()
{
    node *t;
    int i;
    int j = 0;
    const int max = 10;
    printf("--- C AVL Tree Demo  ---\n");
    t = NULL;
    printf("Insert: ");
    for( i = 0; i < max; i++, j = ( j + 7 ) % max )
    {
        t = insert( j, t );
        printf("%d ",j);
 
    }
    printf(" into the tree\n\n");
    display_avl(t);
    dispose(t);
    return 0;
}
