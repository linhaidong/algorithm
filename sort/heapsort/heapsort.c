/*************************************************************************
    > File Name: heapsort.c
    > Author: ma6174
    > Mail: ma6174@163.com 
    > Created Time: 2016年07月28日 星期四 11时17分48秒
 ************************************************************************/
/*time:2015.9.4  author:chen                        */  
/*1.如何建立最大堆                                    */  
/*2.把数组转换成最大堆                               */  
/*3.把建好的堆中数据与原数组进行数据交换              */  
/******************************************************************************/  
  
#include <stdio.h>  
#include <stdlib.h>  
  
void swap(int *x, int *y)  
{  
    int tmp = *x;  
    *x = *y;  
    *y = tmp;  
}  
  
  
  
void max_heapify(int a[], int i, int heapsize)  
{  
    int l = 2 * i;//取其左孩子的坐标  
    int r = 2 * i + 1;//取其右孩子的坐标  
    int largest;//临时变量，用来保存r、l、i三个节点中最大的值  
  
    if (l <= heapsize&&a[l]>a[i])  
        largest = l;  
    else  
        largest = i;  
  
    if (r <= heapsize&&a[r]>a[largest])  
        largest = r;  
  
    if (largest != i)  
    {  
        swap(&a[i], &a[largest]);  
        max_heapify(a, largest, heapsize);  
    }  
}  
  

void buil_max_heap(int a[], int heapsize)  
{ 
    int i;
    for (i = heapsize / 2; i >= 1; i--)  
    {  
        max_heapify(a, i, heapsize);  
    }  
}  
  
void heap_sort(int a[], int heapsize)  
{  
    int i;
    buil_max_heap(a, heapsize);  
    for (i = heapsize; i >= 1; i--)  
    {  
        swap(&a[1], &a[heapsize]);  
        heapsize--;  
        max_heapify(a, 1, heapsize);  
    }  
}  
  
int main()  
{  
    int a[] = { 0, 12, -3, 88, 52, 6, 4, 33, 2, 100, 5, 20,11};  
    heap_sort(a, 12);  
    return 0;  
}  

