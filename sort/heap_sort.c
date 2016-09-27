#include <stdio.h>
#include <stdlib.h>
void swap(int *a, int * b)
{
    int tmp;
    tmp = *a;
    *a = *b;
    *b = tmp;
}
/*堆调整，由于使用算法，停止的条件为节点为叶子节点*/
void heapadjust(int a[], int i, int size)
{
    int lchild = 2*i+1;
    int rchild = 2*i+2;
    int max = i;
    /*只调整非叶子节点*/
    if(i <= (size-1)/2)
    {
        if(lchild <= size && a[lchild] > a[max])
            max = lchild;
        if(rchild <= size && a[rchild] > a[max])
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
    for(i = (size-1)/2; i >= 0; i--)
    {
        heapadjust(a, i, size);
    }
}
/**/
void heapsort(int a[], int size)
{
    int i;
    buildheap(a, size);
    for(i = size; i >= 0; i--)
    {
        swap(&a[i], &a[0]);
        heapadjust(a, 0, i-1);
    }
}
int main()
{
    int a[] = {3,6,9,5,1,8,2,7,4,10};
    heapsort(a, sizeof(a)/sizeof(int));
    return 0;    
}

