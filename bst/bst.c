/*binary search tree*/
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
typedef int TREE_TYPE;

typedef struct bst_tree
{
    TREE_TYPE value;
    struct bst_tree *lchild;
    struct bst_tree *rchild;
}bst_tree, *pbst_tree;
typedef void (*vist_fun)(pbst_tree node);
pbst_tree bst_mknode(TREE_TYPE value)
{
    pbst_tree  tmp;
    tmp =(pbst_tree)calloc(1, sizeof(bst_tree));
    assert(tmp != NULL);
    tmp->rchild = NULL;
    tmp->lchild = NULL;
    tmp->value = value;
    return tmp;
}

int bst_insert(pbst_tree * root, TREE_TYPE value)
{
    pbst_tree  tmp;
    pbst_tree  *pt;
    if(*root == NULL)
    {
        *root = bst_mknode(value);
    }
    else
    {
        tmp = *root;
        /*插入的节点必为叶子节点*/
        /*插入终止条件：节点的孩子节点为空*/
        while(tmp)
        {
            if(value > tmp->value)
            {
                if(tmp->rchild)
                    tmp = tmp->rchild;
                else
                {
                    tmp->rchild = bst_mknode(value);
                    break;
                }
            }
            else if(value < tmp->value)
            {
                if(tmp->lchild)
                    tmp = tmp->lchild;
                else
                {
                    tmp->lchild = bst_mknode(value);
                    break;
                }
            }
            else
                return;
        }
    }
}
void vist(pbst_tree node)
{
    printf("%d", node->value);
}
void bst_pre_vist(pbst_tree node, vist_fun fun)
{
    if(node)
    {
        if(node->lchild)
             bst_pre_vist(node->lchild, fun);
        fun(node);
        if(node->rchild)
            bst_pre_vist(node->rchild, fun);
    }
}
int main()
{   
    pbst_tree root = NULL;
    int a[] = {7,5,8,2,9,1,4,3,6};
    int i;
    for(i = 0; i < 9; i++ )
    {
        bst_insert(&root, a[i]);
    }
    bst_pre_vist(root, vist);
    return 0;
}
