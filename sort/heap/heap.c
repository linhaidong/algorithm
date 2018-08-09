#include <stdio.h>
#include <stdlib.h>

void print(int arr[], int len);
/* --------------------------------------------------------------------------*/
/**
 * @Synopsis 交换操作 
 *
 * @Param a
 * @Param b
 */
/* ----------------------------------------------------------------------------*/
void swap(int *a, int * b)
{
    int tmp;
    tmp = *a;
    *a = *b;
    *b = tmp;
}


void print(int arr[], int len)
{
    int i;
    printf("array:");
    for(i=0; i<len; i++)
    {
        printf("%d, ",arr[i] );
    }
    printf("\r\n");
}

int charg_leaf(int node, int size)
{
    if(size == 1 || size == 0)
        return 0;
    //if (size == 2)
    if(node <= (size/2-1))
        return 1;
    else
        return 0;
}
/*堆调整，由于使用算法，停止的条件为节点为叶子节点*/

/* --------------------------------------------------------------------------*/
/**
 * @Synopsis  
 *
 * @Param a[]   数组
 * @Param i     调整节点的下标
 * @Param size  数组的长度,起到检查是否越界的作用
 */
/* ----------------------------------------------------------------------------*/
void heapadjust(int a[], int i, int size)
{
    int lchild = 2*i+1;
    int rchild = 2*i+2;
    int max = i;
    /*只调整非叶子节点*/
    //if(i <= (size-1)/2)
    //if(i <= (size/2-1))
    if(charg_leaf(i,size) )
    {
        if(lchild < size && a[lchild] > a[max])
            max = lchild;
        if(rchild < size && a[rchild] > a[max])
            max =  rchild;
        /*值不同，需要调整*/
        if(max != i)
        {
            swap(&a[max], &a[i]);
            /*从置换的节点开始调整，防止由于置换，破坏子堆的结构*/
            /*进入下一层，构造堆*/
            heapadjust(a, max, size);
        }
    }
}
/*建立堆*/
int buildheap(int a[], int size)
{
    int i;
    //自底而上，从第一个非叶子节点开始
    //for(i = (size-1)/2; i >= 0; i--)
    for(i = size/2 - 1; i >= 0; i--)
    {
        heapadjust(a, i, size);
    }
}

/* --------------------------------------------------------------------------*/
/**
 * @Synopsis        堆排序
 *
 * @Param a[]
 * @Param size
 */
/* ----------------------------------------------------------------------------*/
void heapsort(int a[], int size)
{
    int i, j;
    
    //建立堆
    buildheap(a, size);
    printf("after heap:\r\n");
    print(a, size);
    
    //交换数据
    for(i = size-1; i > 0; i--)
    {
        swap(&a[i], &a[0]);
        printf("after swap:");
        print(a, size);
        heapadjust(a, 0, i);
        print(a, size);
    }
}

int main()
{
    //int a[] = {3,6,9,5,1,8,2,7,4,10};
    int a[] = {4,6,8,5,9};
    //int a[] = {4,8,5};
    int len = sizeof(a)/sizeof(int);
    print(a, len);
    heapsort(a, len);
    printf("after sort:\r\n");
    print(a, len);
    return 0;    
}

