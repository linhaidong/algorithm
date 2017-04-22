/*************************************************************************
    > File Name: mgsort.c
    > Author: ma6174
    > Mail: ma6174@163.com 
    > Created Time: 2016年07月20日 星期三 15时15分10秒
 ************************************************************************/

#include <stdio.h>
#include <stdlib.h>
//将同一数组内的两个连续的有序序列归并
int merge(int array[], int low, int mid, int higt)
{
    int num = higt - low + 1;
    int tmp_array[num];
    int turn = 0;
    int i =  low, j = mid + 1;
    while(i <=  mid && j <= higt)
    {
#if 0
        if(array[i] > array[j])
            tmp_array[turn++] = array[i++];
        else
            tmp_array[turn++] = array[j++];
#endif
        tmp_array[turn++] = array[i] > array[j] ? array[i++] : array[j++];
    }
    while(i <= mid)
        tmp_array[turn++] = array[i++];
    while(j <= higt)
        tmp_array[turn++] = array[j++];
    for(turn = 0; turn < num; turn++)
    {
        array[low+turn] = tmp_array[turn];
    }
    return 0;
}
//递归实现 归并排序
int mgsort(int array[], int  low, int high)
{
    int mid;
    if(low < high)
    {
        mid = (low+high)/2;
        mgsort(array, low, mid);
        mgsort(array, mid+1, high);
        merge(array, low, mid, high);
    }
    return 0;

}
void  print_array(int array[], int num)
{
    int i;
    for(i = 0 ; i < num; i++)
        printf("%3d", *(array+i));
    printf("\r\n");
}
int main()
{
  int  array[7] = {3, 6, 4, 9, 7, 5, 8};
  mgsort(array, 0, 6);
  print_array(array, 6);
  return 0;
}
