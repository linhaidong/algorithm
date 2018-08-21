/*************************************************************************
    > File Name: avl.h
    > Author: linengier
    > Mail: linengier@126.com 
    > Created Time: 2016年09月27日 星期二 08时01分25秒
 ************************************************************************/
#ifndef AVLTREE_H_INCLUDED
#define AVLTREE_H_INCLUDED
 
typedef struct node
{
    int data;
    int height;
    struct node*  left;
    struct node*  right;
}node;
 
 
void dispose(node* t);
node* find( int e, node *t );
node* find_min( node *t );
node* find_max( node *t );
node* insert( int data, node *t );
node* delete( int data, node *t );
void display_avl(node* t);
int get( node* n );
#endif // AVLTREE_H_INCLUDED
