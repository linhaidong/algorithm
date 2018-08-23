/*************************************************************************
    > File Name: tt.c
    > Author:     linhaidong
    > Mail:       linhaidong@alibaba-inc.com 
    > Time:      2018年08月21日 星期二 16时29分20秒
    > Abstract: 
*****************************************************/
#include <stdlib.h> 
#include <stdio.h> 
#include "tt.h" 

btree search(typekey, btree); 
btree insert(typekey,btree); 
btree Delete(typekey,btree); 
int height(btree); 
int count(btree); 
double payload(btree); 
btree deltree(btree); 

static void InternalInsert(typekey, btree); 
static void InsInNode(btree, int); 
static void SplitNode(btree, int); 
static btree NewRoot(btree); 

static void InternalDelete(typekey, btree); 
static void JoinNode(btree, int); 
static void MoveLeftNode(btree t, int); 
static void MoveRightNode(btree t, int); 
static void DelFromNode(btree t, int); 
static btree FreeRoot(btree); 

static btree delall(btree); 
static void Error(int,typekey); 

int btree_disp; /* 查找时找到的数据元素在节点中的位置 */ 
char * InsValue = NULL; /* 与要插的数据元素相对应的值 */ 
static int flag; /* 节点增减标志 */ 
static int btree_level = 0; /* 多路树的高度 */ 
static int btree_count = 0; /* 多路树的数据元素总数 */ 
static int node_sum = 0;  /* 多路树的节点总数 */ 
static int level; /* 当前访问的节点所处的高度 */ 
static btree NewTree; /* 在节点分割的时候指向新建的节点 */ 
static typekey InsKey; /* 要插入的数据元素 */ 

btree search(typekey key, btree t) 
{ 
    int i,j,m; 
    level=btree_level-1; 
    while (level >= 0){ 
        for(i=0, j=t->d-1; i<j; m=(j+i)/2, (key > t->k[m])?(i=m+1):(j=m)); 
        if (key == t->k [ i ]){ 
            btree_disp = i; 
            return t; 
        } 
        if (key > t->k [ i ]) /* i == t->d-1 时有可能出现 */ 
            i++; 
        t = t->p[ i ]; 
        level--; 
    } 
    return NULL; 
} 

btree insert(typekey key, btree t) 
{ 
    level=btree_level; 
    InternalInsert(key, t); 
    if (flag == 1)  /* 根节点满之后，它被分割成两个半满节点 */ 
        t=NewRoot(t);    /* 树的高度增加 */ 
    return t; 
} 

void InternalInsert(typekey key, btree t) 
{ 
    int i,j,m; 

    level--; 
    if (level < 0){ /* 到达了树的底部: 指出要做的插入 */ 
        NewTree = NULL; /* 这个数据元素没有对应的子树 */ 
        InsKey = key; /* 导致底层的叶子节点增加数据元素值+空子树对 */ 
        btree_count++; 
        flag = 1; /* 指示上层节点把返回的数据元素插入其中 */ 
        return; 
    } 
    for(i=0, j=t->d-1; i<j; m=(j+i)/2, (key > t->k[m])?(i=m+1):(j=m)); 
    if (key == t->k[ i ]) { 
        Error(1,key); /* 数据元素已经在树中 */ 
        flag = 0; 
        return; 
    } 
    if (key > t->k[ i ]) /* i == t->d-1 时有可能出现 */ 
        i++; 
    InternalInsert(key, t->p[ i ]); 

    if (flag == 0) 
        return; 
    /* 有新数据元素要插入到当前节点中 */ 
    if (t->d < 2*M) {/* 当前节点未满 */ 
        InsInNode(t, i); /* 把数据元素值+子树对插入当前节点中 */ 
        flag = 0; /* 指示上层节点没有需要插入的数据元素值+子树，插入过程结束 */ 
    } 
    else /* 当前节点已满，则分割这个页面并把数据元素值+子树对插入当前节点中 */ 
        SplitNode(t, i); /* 继续指示上层节点把返回的数据元素值+子树插入其中 */ 
} 

/* 
* 把一个数据元素和对应的右子树插入一个节点中 
*/ 
void InsInNode(btree t, int d) 
{ 
    int i; 
    /* 把所有大于要插入的数据元素值的数据元素和对应的右子树右移 */ 
    for(i = t->d; i > d; i--){ 
        t->k[ i ] = t->k[i-1]; 
        t->v[ i ] = t->v[i-1]; 
        t->p[i+1] = t->p[ i ]; 
    } 
    /* 插入数据元素和右子树 */ 
    t->k[ i ] = InsKey; 
    t->p[i+1] = NewTree; 
    t->v[ i ] = InsValue; 
    t->d++; 
} 
/* 
* 前件是要插入一个数据元素和对应的右子树，并且本节点已经满 
* 导致分割这个节点，插入数据元素和对应的右子树， 
* 并向上层返回一个要插入数据元素和对应的右子树 
*/ 
void SplitNode(btree t, int d) 
{     
    int i,j; 
    btree temp; 
    typekey temp_k; 
    char *temp_v; 
    /* 建立新节点 */ 
    temp = (btree)malloc(sizeof(node)); 
    /* 
     *   +---+--------+-----+-----+--------+-----+ 
     *   | 0 | ...... |  M  | M+1 | ...... |2*M-1| 
     *   +---+--------+-----+-----+--------+-----+ 
     *   |<-      M+1     ->|<-        M-1     ->|   
     */ 
    if (d > M) { /* 要插入当前节点的右半部分 */ 
        /* 把从 2*M-1 到 M+1 的 M-1 个数据元素值+子树对转移到新节点中, 
         * 并且为要插入的数据元素值+子树空出位置 */ 
        for(i=2*M-1,j=M-1; i>=d; i--,j--) { 
            temp->k[j] = t->k[ i ]; 
            temp->v[j] = t->v[ i ]; 
            temp->p[j+1] = t->p[i+1]; 
        } 
        for(i=d-1,j=d-M-2; j>=0; i--,j--) { 
            temp->k[j] = t->k[ i ]; 
            temp->v[j] = t->v[ i ]; 
            temp->p[j+1] = t->p[i+1]; 
        } 
        /* 把节点的最右子树转移成新节点的最左子树 */ 
        temp->p[0] = t->p[M+1]; 
        /* 在新节点中插入数据元素和右子树 */ 
        temp->k[d-M-1] = InsKey; 
        temp->p[d-M] = NewTree; 
        temp->v[d-M-1] = InsValue; 
        /* 设置要插入上层节点的数据元素和值 */ 
        InsKey = t->k[M]; 
        InsValue = t->v[M]; 

    } 
    else { /* d <= M */ 
        /* 把从 2*M-1 到 M 的 M 个数据元素值+子树对转移到新节点中 */ 
        for(i=2*M-1,j=M-1; j>=0; i--,j--) { 
            temp->k[j] = t->k[ i ]; 
            temp->v[j] = t->v[ i ]; 
            temp->p[j+1] = t->p[i+1]; 
        } 
        if (d == M) /* 要插入当前节点的正中间 */ 
            /* 把要插入的子树作为新节点的最左子树 */ 
            temp->p[0] = NewTree; 
            /* 直接把要插入的数据元素和值返回给上层节点 */ 
        else { /* (d<M) 要插入当前节点的左半部分 */ 
            /* 把节点当前的最右子树转移成新节点的最左子树 */ 
            temp->p[0] = t->p[M]; 
            /* 保存要插入上层节点的数据元素和值 */ 
            temp_k = t->k[M-1]; 
            temp_v = t->v[M-1]; 
            /* 把所有大于要插入的数据元素值的数据元素和对应的右子树右移 */ 
            for(i=M-1; i>d; i--) { 
                t->k[ i ] = t->k[i-1]; 
                t->v[ i ] = t->v[i-1]; 
                t->p[i+1] = t->p[ i ]; 
            } 
            /* 在节点中插入数据元素和右子树 */ 
            t->k[d] = InsKey; 
            t->p[d+1] = NewTree; 
            t->v[d] = InsValue; 
            /* 设置要插入上层节点的数据元素和值 */ 
            InsKey = temp_k; 
            InsValue = temp_v; 
        } 
    } 
    t->d =M; 
    temp->d = M; 
    NewTree = temp; 
    node_sum++; 
} 

btree Delete(typekey key, btree t) 
{ 
    level=btree_level; 
    InternalDelete(key, t); 
    if (t->d == 0) 
    /* 根节点的子节点合并导致根节点数据元素的数目随之减少， 
     * 当根节点中没有数据元素的时候，只有它的最左子树可能非空 */ 
        t=FreeRoot(t); 
    return t; 
} 

void InternalDelete(typekey key, btree t) 
{ 
    int i,j,m; 
    btree l,r; 
    int lvl; 

    level--; 
    if (level < 0) { 
        Error(0,key); /* 在整个树中未找到要删除的数据元素 */ 
        flag = 0; 
        return; 
    } 
    for(i=0, j=t->d-1; i<j; m=(j+i)/2, (key > t->k[m])?(i=m+1):(j=m)); 
    if (key == t->k[ i ]) { /* 找到要删除的数据元素 */ 
        if (t->v[ i ] != NULL) 
            free(t->v[ i ]); /* 释放这个节点包含的值 */ 
        if (level == 0) { /* 有子树为空则这个数据元素位于叶子节点 */ 
            DelFromNode(t,i); 
            btree_count--; 
            flag = 1; 
            /* 指示上层节点本子树的数据元素数量减少 */ 
            return; 
        } else { /* 这个数据元素位于非叶节点 */ 
            lvl = level-1; 
            /* 找到前驱节点 */ 
            r = t->p[ i ]; 
            while (lvl > 0)  { 
                r = r->p[r->d]; 
                lvl--; 
            } 
            t->k[ i ]=r->k[r->d-1]; 
            t->v[ i ]=r->v[r->d-1]; 
            r->v[r->d-1]=NULL; 
            key = r->k[r->d-1]; 
        } 
    } 
    else if (key > t->k[ i ]) /* i == t->d-1 时有可能出现 */ 
        i++;          
    InternalDelete(key,t->p[ i ]); 
    /* 调整平衡 */ 
    if (flag == 0) 
        return; 
    if (t->p[ i ]->d < M) { 
        if (i == t->d) /* 在最右子树中发生了删除 */ 
            i--; /* 调整最右数据元素的左右子树平衡 */ 
        l = t->p [ i ]; 
        r = t->p[i+1]; 
        if (r->d > M) 
            MoveLeftNode(t,i); 
        else if(l->d > M) 
            MoveRightNode(t,i); 
        else { 
            JoinNode(t,i); 
            /* 继续指示上层节点本子树的数据元素数量减少 */ 
            return; 
        } 
        flag = 0; 
        /* 指示上层节点本子树的数据元素数量没有减少，删除过程结束 */ 
    } 
} 

/* 
* 合并一个节点的某个数据元素对应的两个子树 
*/ 
void JoinNode(btree t, int d) 
{ 
    btree l,r; 
    int i,j; 
    l = t->p[d]; 
    r = t->p[d+1]; 

    /* 把这个数据元素下移到它的左子树 */ 
    l->k[l->d] = t->k[d]; 
    l->v[l->d] = t->v[d]; 
    /* 把右子树中的所有数据元素值和子树转移到左子树 */ 
    for (j=r->d-1,i=l->d+r->d; j >= 0 ; j--,i--) { 
        l->k[ i ] = r->k[j]; 
        l->v[ i ] = r->v[j]; 
        l->p[ i ] = r->p[j]; 
    } 
    l->p[l->d+r->d+1] = r->p[r->d]; 
    l->d += r->d+1; 
    /* 释放右子树的节点 */ 
    free(r); 
    /* 把这个数据元素右边的数据元素和对应的右子树左移 */ 
    for (i=d; i < t->d-1; i++) { 
        t->k[ i ] = t->k[i+1]; 
        t->v[ i ] = t->v[i+1]; 
        t->p[i+1] = t->p[i+2]; 
    } 
    t->d--; 
    node_sum--; 
} 
/* 
* 从一个数据元素的右子树向左子树转移一些数据元素，使两个子树平衡 
*/ 
void MoveLeftNode(btree t, int d) 
{ 
    btree l,r; 
    int m; /* 应转移的数据元素的数目 */ 
    int i,j; 
    l = t->p[d]; 
    r = t->p[d+1]; 
    m = (r->d - l->d)/2; 

    /* 把这个数据元素下移到它的左子树 */ 
    l->k[l->d] = t->k[d]; 
    l->v[l->d] = t->v[d]; 
    /* 把右子树的最左子树转移成左子树的最右子树 
     * 从右子树向左子树移动 m-1 个数据元素+子树对 */ 
    for (j=m-2,i=l->d+m-1; j >= 0; j--,i--) { 
        l->k[ i ] = r->k[j]; 
        l->v[ i ] = r->v[j]; 
        l->p[ i ] = r->p[j]; 
    } 
    l->p[l->d+m] = r->p[m-1]; 
    /* 把右子树的最左数据元素提升到这个数据元素的位置上 */ 
    t->k[d] = r->k[m-1]; 
    t->v[d] = r->v[m-1]; 
    /* 把右子树中的所有数据元素值和子树左移 m 个位置 */ 
    r->p[0] = r->p[m]; 
    for (i=0; i<r->d-m; i++) { 
        r->k[ i ] = r->k[i+m]; 
        r->v[ i ] = r->v[i+m]; 
        r->p[ i ] = r->p[i+m]; 
    } 
    r->p[r->d-m] = r->p[r->d]; 
    l->d+=m; 
    r->d-=m; 
} 
/* 
* 从一个数据元素的左子树向右子树转移一些数据元素，使两个子树平衡 
*/ 
void MoveRightNode(btree t, int d) 
{ 
    btree l,r; 
    int m; /* 应转移的数据元素的数目 */ 
    int i,j; 
    l = t->p[d]; 
    r = t->p[d+1]; 

    m = (l->d - r->d)/2; 
    /* 把右子树中的所有数据元素值和子树右移 m 个位置 */ 
    r->p[r->d+m]=r->p[r->d]; 
    for (i=r->d-1; i>=0; i--) { 
        r->k[i+m] = r->k[ i ]; 
        r->v[i+m] = r->v[ i ]; 
        r->p[i+m] = r->p[ i ]; 
    } 
    /* 把这个数据元素下移到它的右子树 */ 
    r->k[m-1] = t->k[d]; 
    r->v[m-1] = t->v[d]; 
    /* 把左子树的最右子树转移成右子树的最左子树 */ 
    r->p[m-1] = l->p[l->d]; 
    /* 从左子树向右子树移动 m-1 个数据元素+子树对 */ 
    for (i=l->d-1,j=m-2; j>=0; j--,i--) { 
        r->k[j] = l->k[ i ]; 
        r->v[j] = l->v[ i ]; 
        r->p[j] = l->p[ i ]; 
    } 
    /* 把左子树的最右数据元素提升到这个数据元素的位置上 */ 
    t->k[d] = l->k[ i ]; 
    t->v[d] = l->v[ i ]; 
    l->d-=m; 
    r->d+=m; 
} 
/* 
* 把一个数据元素和对应的右子树从一个节点中删除 
*/ 
void DelFromNode(btree t, int d) 
{ 
    int i; 
    /* 把所有大于要删除的数据元素值的数据元素左移 */ 
    for(i=d; i < t->d-1; i++) { 
        t->k[ i ] = t->k[i+1]; 
        t->v[ i ] = t->v[i+1]; 
    } 
    t->d--; 
} 
/* 
* 建立有两个子树和一个数据元素的根节点 
*/ 
btree NewRoot(btree t) 
{ 
    btree temp; 
    temp = (btree)malloc(sizeof(node)); 
    temp->d = 1; 
    temp->p[0] = t; 
    temp->p[1] = NewTree; 
    temp->k[0] = InsKey; 
    temp->v[0] = InsValue; 
    btree_level++; 
    node_sum++; 
    return(temp); 
} 
/* 
* 释放根节点，并返回它的最左子树 
*/ 
btree FreeRoot(btree t) 
{ 
    btree temp; 
    temp = t->p[0]; 
    free(t); 
    btree_level--; 
    node_sum--; 
    return temp; 
} 

void Error(int f,typekey key) 
{ 
    if (f) 
        printf("Btrees error: Insert %d!/n",key); 
    else 
        printf("Btrees error: delete %d!/n",key); 
} 

int height(btree t) 
{ 
    return btree_level; 
} 

int count(btree t) 
{ 
    return btree_count; 
} 
double payload(btree t) 
{ 
    if (node_sum==0) 
        return 1; 
    return (double)btree_count/(node_sum*(2*M)); 
} 
btree deltree (btree t) 
{     
    level=btree_level; 
    btree_level = 0; 
    return delall(t); 

} 
btree delall(btree t) 
{ 
    int i; 
    level--; 
    if (level >= 0) { 
        for (i=0; i < t->d; i++) 
            if (t->v[ i ] != NULL) 
                free(t->v[ i ]); 
        if (level > 0) 
            for (i=0; i<= t->d ; i++) 
                t->p[ i ]=delall(t->p[ i ]); 
        free(t); 
    } 
    return NULL; 
}
int main()
{
    ;
} 
