/*************************************************************************
    > File Name: tt.h
    > Author:     linhaidong
    > Mail:       linhaidong@alibaba-inc.com 
    > Time:      2018年08月21日 星期二 17时25分42秒
    > Abstract: 
 ************************************************************************/
#define M 1 
typedef int typekey; 
typedef struct btnode {    /* B-Tree 节点 */ 
    int d;    /* 节点中数据元素的数目 */ 
    typekey k[2*M];    /* 数据元素 */ 
    char *v[2*M];    /* 值 */ 
    struct btnode *p[2*M+1];    /* 指向子树的指针 */ 
} node, *btree; 
/* 
* 每个数据元素的左子树中的所有的数据元素都小于这个数据元素， 
* 每个数据元素的右子树中的所有的数据元素都大于等于这个数据元素。 
* 叶子节点中的每个数据元素都没有子树。 
*/ 

/* 当 M 等于 1 时也称为 2-3 树 
*    +----+----+ 
*    | k0 | k1 |                     
*  +-+----+----+--- 
*  | p0 | p1 | p2 | 
*  +----+----+----+ 
*/ 
extern int btree_disp; /* 查找时找到的数据元素在节点中的位置 */ 
extern char * InsValue; /* 与要插的数据元素相对应的值 */ 
extern btree search(typekey, btree); 
extern btree insert(typekey,btree); 
extern btree Delete(typekey,btree); 
extern int height(btree); 
extern int count(btree); 
extern double payload(btree); 
extern btree deltree(btree); 
/* end of btrees.h */ 


