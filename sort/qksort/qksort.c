/*************************************************************************
    > File Name: qksort.c
    > Author: ma6174
    > Mail: ma6174@163.com 
    > Created Time: 2016年07月19日 星期二 16时42分19秒
 ************************************************************************/

#include <stdio.h>
#include <stdlib.h>
int adjust_array(int array[], int i, int j)
{
    int key;
    key = array[i];
    while(i < j)
    {
        //从右向左找小于
        while(i < j && array[j] >= key)
           j--;
        if(i < j)
        {
            array[i] = array[j];
            //i++;
        }
        //从做向右找大于
        while((i < j) && array[i] <= key)
            i++;
        if(i < j)
        {
          array[j] = array[i];
          //j--;
        }
    }
    array[i]=key;
    return i;

}
void  qksort(int array[], int i, int j)
{
    if(i < j)
    {
        int mid = adjust_array(array, i, j);
        qksort(array, i, mid-1);
        qksort(array, mid+1, j);
        //adjust_array(array, i, mid-1);
        //adjust_array(array, mid+1, j);
    }
}
int main()
{
    int array[7]={8, 6, 4, 9, 7, 5, 3};
    int array2[10] = {3,7,2,5,8,1,4,9,6,10};
    qksort(array, 0, 6);
    qksort(array2, 0, 9);
    int i;
    for(i=0; i < 7; i++)
        printf("%3d", array[i]);
    printf("\r\n");
    for(i=0; i < 10; i++)
        printf("%3d", array2[i]);
    printf("\r\n");
    return 0;
}
