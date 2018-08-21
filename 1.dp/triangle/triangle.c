/*************************************************************************
    > File Name: triangle.c
    > Author:     linhaidong
    > Mail:       linengier@126.com 
    > Time:      2017年04月22日 星期六 09时27分50秒
    > Abstract: 
 ************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


#include <stdio.h>  
#define MAXN 200  

int max(int a,int b)  
{  
    if(a>b) return a;  
    return b;  
} 

int f[10][10];
/*triangle exprgess by array*/
int map[5][5] = {
    {7},
    {3,8,},
    {8,1,0},
    {2,7,4,4},
    {4,5,2,6,5},
};
int map2[5][5] = {
    {6},
    {3,9},
    {8,7,5},
    {4,5,8,2},
    {10,6,9,3,6}
};
int calculate_result(int  map[][5], int num)  
{  
    int n,i,j;  
    int maxf=-1;  

    n = num;
    memset(f, 0, sizeof(f));
    /*line num control*/
    for(i=0;i < n;i++)  
        for(j=0;j <= i;j++) { /*control for every line for every num*/   
            
            /*get status by previous step*/
            if(j == 0) {
                /*tree most left node, only add previous line head*/
                f[i][j]=f[i-1][j];  
            }
            else if(j==i) {
                /*tree most right node, only add previous line tail*/
                f[i][j]=f[i-1][j-1];  
            }
            else {
                /*node has left and right parent,should be compared to get bigger*/
                f[i][j]=max(f[i-1][j], f[i-1][j-1]);  
            }
            /*calculate current step result*/
            f[i][j]+=map[i][j];  
        }

    /*when all the num has been calculated, get the loggest path in last line*/
    for(i=0; i < n; i++)  
        maxf=max(maxf,f[n-1][i]);  
    printf("max path len is %d\n",maxf); 
    /*print max path*/
    int index = 0;
    for(i = 0; i < n; i++) {
        if (maxf == f[n-1][i]){
            index = i;
            break;
        }
    }
    printf("index is %d\r\n", index);
    printf("path is ");
    printf("%d, ", map[n-1][index]);
    for (i = n-1; i > 0; i--) {
        if (index == 0){
            printf("%d, ", map[i-1][index]);
        } else if(index-1 == i) {
            index -= 1;
            printf("%d, ", map[i-1][index -1]);
        } else {
            if (f[i-1][index] >= f[i-1][index -1])
                printf("%d, ", map[i-1][index]);
            else {
                printf("%d, ", map[i-1][index -1]);
                index -= 1;
            }
        }
    }
    printf("\r\n");
    return 0;  
}  

int main()
{
    calculate_result(map, 5);
    calculate_result(map2, 5);
    return 0;
}

