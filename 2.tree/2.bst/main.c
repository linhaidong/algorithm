/*************************************************************************
    > File Name: main.c
    > Author:     linhaidong
    > Mail:       linhaidong@alibaba-inc.com 
    > Time:      2018年08月21日 星期二 14时41分35秒
    > Abstract: 
 ************************************************************************/
#include <stdio.h>
#include "bst.h"

void vist(pbst_tree node)
{
    printf("%d\r\n", node->value);
}
int main()
{   
    pbst_tree root = NULL;
    int a[] = {7,5,8,2,9,1,4,3,6};
    int i;
    for(i = 0; i < 9; i++ )
    {
        Bst_insert(&root, a[i]);
    }
    Bst_last_vist(root, vist);
    Free_tree(root);
    return 0;
}
