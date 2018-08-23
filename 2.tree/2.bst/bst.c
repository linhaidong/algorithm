/*binary search tree*/
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "bst.h"
static pbst_tree mknode(TREE_TYPE value)
{
    pbst_tree  tmp;
    tmp =(pbst_tree)calloc(1, sizeof(bst_tree));
    assert(tmp != NULL);
    tmp->rchild = NULL;
    tmp->lchild = NULL;
    tmp->value = value;
    return tmp;
}

static void freenode(pbst_tree node)
{
    if(node)
        free(node);
}

int Bst_insert(pbst_tree * root, TREE_TYPE value)
{
    pbst_tree  tmp;
    pbst_tree  *pt;

    //根节点为空，直接设置根节点
    if(*root == NULL)
    {
        *root = mknode(value);
    }
    else
    {
        tmp = *root;
        /*插入的节点必为叶子节点*/
        /*插入终止条件：节点的孩子节点为空*/
        while(tmp)
        {
            //大于插入右侧
            if(value > tmp->value)
            {
                //右节点存在，则赋值指针为右孩子
                if(tmp->rchild)
                    tmp = tmp->rchild;
                else
                {
                    //右孩子为空，直接赋值给右孩子
                    tmp->rchild =  mknode(value);
                    break;
                }
            }//小于插入左侧
            else if(value < tmp->value)
            {
                if(tmp->lchild)
                    tmp = tmp->lchild;
                else
                {
                    tmp->lchild = mknode(value);
                    break;
                }
            }
            else
                return 0;
        }
    }
    return 0;
}

/* --------------------------------------------------------------------------*/
/**
 * @Synopsis  
 *
 * @Param root
 * @Param fun
 */
/* ----------------------------------------------------------------------------*/
void bst_vist_normal(pbst_tree root, vist_fun fun)
{
    return;
}
/* --------------------------------------------------------------------------*/
/**
 * @Synopsis  递归后序遍历,用于删除
 *            树的前序，种序，后续遍历，以根节点为判断标准
 *            前序：先遍历根节点
 *            中序：先遍历左孩子，再遍历根根节点，再遍历右孩子
 * @Param node
 */
/* ----------------------------------------------------------------------------*/
void Bst_last_vist(pbst_tree node, vist_fun fun)
{
    if(node)
    {
        if(node->lchild)
            Bst_last_vist(node->lchild, fun);
        if(node->rchild)
            Bst_last_vist(node->rchild, fun);
        fun(node);
    }
}

/* --------------------------------------------------------------------------*/
/**
 * @Synopsis  释放空间
 *            利用后续遍历释放空间
 
 * @Returns   
 */
/* ----------------------------------------------------------------------------*/
void node_free(pbst_tree node)
{
    printf("free node %d\r\n", node->value);
    freenode(node);
}
void Free_tree(pbst_tree root)
{
    Bst_last_vist(root, node_free);
}


//TODO
//get bst high
//

