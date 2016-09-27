/*************************************************************************
    > File Name: avl.c
    > Author: linengier
    > Mail: linengier@126.com 
    > Created Time: 2016年09月27日 星期二 08时02分16秒
 ************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "avl.h"
/*
    remove all nodes of an AVL tree
*/
void dispose(node* t)
{
    if( t != NULL )
    {
        dispose( t->left );
        dispose( t->right );
        free( t );
    }
}
 
/*
    find a specific node's key in the tree
*/
node* find(int e, node* t )
{
    if( t == NULL )
        return NULL;
    if( e < t->data )
        return find( e, t->left );
    else if( e > t->data )
        return find( e, t->right );
    else
        return t;
}
 
/*
    find minimum node's key
*/
node* find_min( node* t )
{
    if( t == NULL )
        return NULL;
    else if( t->left == NULL )
        return t;
    else
        return find_min( t->left );
}
 
/*
    find maximum node's key
*/
node* find_max( node* t )
{
    if( t != NULL )
        while( t->right != NULL )
            t = t->right;
 
    return t;
}
 
/*
    get the height of a node
*/
static int height( node* n )
{
    if( n == NULL )
        return -1;
    else
        return n->height;
}
 
/*
    get maximum value of two integers
*/
static int max( int l, int r)
{
    return l > r ? l: r;
}
 
/*
    perform a rotation between a k2 node and its left child
    note: call single_rotate_with_left only if k2 node has a left child
*/
 
static node* single_rotate_with_left( node* k2 )
{
    node* k1 = NULL;
 
    k1 = k2->left;
    /*设置右孩子节点为父亲的左孩子*/
    k2->left = k1->right;
    /*父节点左旋转*/
    k1->right = k2;
 
    /*设置调整的节点的高度*/
    k2->height = max( height( k2->left ), height( k2->right ) ) + 1;
    k1->height = max( height( k1->left ), k2->height ) + 1;
    /*返回此子树的根节点，方便上级函数与此子树建立关联*/
    return k1; /* new root */
}
 
/*
    perform a rotation between a node (k1) and its right child
    note: call single_rotate_with_right only if
    the k1 node has a right child
*/
 
static node* single_rotate_with_right( node* k1 )
{
    node* k2;
 
    k2 = k1->right;
    /*设置左孩子，为根节点的右子树*/
    k1->right = k2->left;
    /*父节点右旋，变为右孩子的左子树*/
    k2->left = k1;
 
    k1->height = max( height( k1->left ), height( k1->right ) ) + 1;
    k2->height = max( height( k2->right ), k1->height ) + 1;
 
    /*返回此子树的根节点，方便上级函数与此子树建立关联*/
    return k2;  /* New root */
}
 
/*
    perform the left-right double rotation,
    note: call double_rotate_with_left only if k3 node has
    a left child and k3's left child has a right child
*/
 
static node* double_rotate_with_left( node* k3 )
{
    /* Rotate between k1 and k2 */
    /*左子树右旋转，变为“左左”结构*/
    k3->left = single_rotate_with_right( k3->left );
 
    /*根节点左旋转,恢复平衡*/
    /* Rotate between K3 and k2 */
    return single_rotate_with_left( k3 );
}
 
/*
    perform the right-left double rotation
 
   notes: call double_rotate_with_right only if k1 has a
   right child and k1's right child has a left child
*/
 
 
 
static node* double_rotate_with_right( node* k1 )
{
    /* rotate between K3 and k2 */
    k1->right = single_rotate_with_left( k1->right );
 
    /* rotate between k1 and k2 */
    return single_rotate_with_right( k1 );
}
 
/*
    insert a new node into the tree
*/
node* insert(int e, node* t )
{
    if( t == NULL )
    {
        /* Create and return a one-node tree */
        t = (node*)malloc(sizeof(node));
        if( t == NULL )
        {
            fprintf (stderr, "Out of memory!!! (insert)\n");
            exit(1);
        }
        else
        {
            t->data = e;
            t->height = 0;
            t->left = t->right = NULL;
        }
    }
    /*插入左子树*/
    else if(e < t->data)
    {
        /*父节点的左孩子赋值(同一级处理)*/
        t->left = insert(e, t->left );
        if(height( t->left ) - height( t->right ) == 2 )
        {
            /*与左叶子节点比较，判断节点在左子树*/
            /*左子树插入左节点，单左旋根节点*/
            if(e < t->left->data)
                t = single_rotate_with_left( t );
            else
                t = double_rotate_with_left( t );
        }
    }
    else if( e > t->data )
    {
        t->right = insert( e, t->right );
        if( height( t->right ) - height( t->left ) == 2 )
        {
            if( e > t->right->data )
                t = single_rotate_with_right( t );
            else
                t = double_rotate_with_right( t );
        }
    }
    /* Else X is in the tree already; we'll do nothing */
    /*重新计算节点的高度*/
    t->height = max( height( t->left ), height( t->right ) ) + 1;
    return t;
}
 
/*
    remove a node in the tree
*/
node* delete( int e, node* t )
{
    printf( "Sorry; Delete is unimplemented; %d remains\n", e );
    return t;
}
 
/*
    data data of a node
*/
int get(node* n)
{
    return n->data;
}
 
/*
    Recursively display AVL tree or subtree
*/
void display_avl(node* t)
{
    if (t == NULL)
        return;
    printf("%d",t->data);
 
    if(t->left != NULL)
        printf("(L:%d)",t->left->data);
    if(t->right != NULL)
        printf("(R:%d)",t->right->data);
    printf("\n");
 
    display_avl(t->left);
    display_avl(t->right);
}
