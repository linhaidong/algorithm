/*************************************************************************
    > File Name: bst.h
    > Author:     linhaidong
    > Mail:       linhaidong@alibaba-inc.com 
    > Time:      2018年08月21日 星期二 14时42分14秒
    > Abstract: 
 ************************************************************************/
#ifndef LINENGIER_BST_TREE_H
#define LINENGIER_BST_TREE_H
typedef int TREE_TYPE;
typedef struct bst_tree
{
    TREE_TYPE value;
    struct bst_tree *lchild;
    struct bst_tree *rchild;
}bst_tree, *pbst_tree;
typedef void (*vist_fun)(pbst_tree node);
extern  int  Bst_insert(pbst_tree * root, TREE_TYPE value);
extern  void Bst_last_vist(pbst_tree node, vist_fun fun);
extern  void Free_tree(pbst_tree root);
#endif

