/*************************************************************************
    > File Name: long_num_char.c
    > Author:     linhaidong
    > Mail:       linengier@126.com
    > Time:      2020年04月18日 星期六 09时32分37秒
    > Abstract: If you have any question, please tell me!
 ************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
//#define DEBUG 1
typedef enum oper_type{
    LEN_BOTH_ZERO = 0,
    LEN_ONE_ZERO,
    LEN_NOT_EMPTY
}oper_type_t;

typedef enum result_type{
    FIRST_ZERO = 0,
    FIRST_AVAILABLE
}result_type_t;
/* --------------------------------------------------------------------------*/
/**
 * @Synopsis  构建一个符合处理逻辑的结构，增加存储结构，减少逻辑结构
 *            这个结构体，内部自包含逻辑性
 */
/* ----------------------------------------------------------------------------*/
//增加s1和S2的指针，使用数据结构标示内部的逻辑
//s1的长度大于S2的长度
typedef struct elem_len{
    oper_type_t type;
    char * s1;
    char * s2;
    int len1;
    int len2;
    int res_len;
}elem_len_t;

typedef struct reslut{
    char * rel_result;
    char * oper_result;
    result_type_t  type;
}result_t;

/* --------------------------------------------------------------------------*/
/**
 * @Synopsis  把外界无逻辑的对象，转化为内部自包含逻辑的对象
 *            内聚，体现事物的本质属性, 使事物表现出一种逻辑的组合关系
 *
 * @Param s1
 * @Param s2
 * @Param elems 输出具有内部逻辑属性的新对象
 *
 * @Returns   
 * 把长度单独定义一个对象，把所有的长度包含在里面，防止长度的重复计算
 */
/* ----------------------------------------------------------------------------*/
int length_charge(char* s1, char *s2, elem_len_t * elems){
    int ret = 0;
    int len1 = strlen(s1);
    int len2 = strlen(s2);
    if (len1 == 0 && len2 == 0){
        elems->res_len = 0;
        elems->type = LEN_BOTH_ZERO;
        return ret; 
    }
    if (len1 == 0){
        elems->s1 = s2;
        elems->len1 = len2;
        elems->res_len = len2;
        elems->type = LEN_ONE_ZERO;
        return ret;
    }
    if (len2 == 0){
        elems->s1 = s1;
        elems->len1 = len1;
        elems->res_len = len1;
        elems->type = LEN_ONE_ZERO;
        return ret;
    }
    if (len1 >= len2){
        elems->s1 = s1;
        elems->len1 = len1;
        elems->s2 = s2;
        elems->len2 = len2;
    }else{
        elems->s1 = s2;
        elems->len1 = len2;
        elems->s2 = s1;
        elems->len2 = len1;
    }
    elems->type = LEN_NOT_EMPTY;
    elems->res_len  = len1 >len2 ? len1:len2;
    return 3;
}

/* --------------------------------------------------------------------------*/
/**
 * @Synopsis  
 * string add operation
 *
 * 代码中添加自然逻辑
 * 利用默认的属性，减少计算机的运算量
 * 
 * 原理：把握事物自身的属性，结合一般的运算规律，分析出最小的运算单位，
 *       设定操作的边界，和尾部处理情况
 * 
 * 实施步骤：
 * 通过加法运算的分析，应该是从低位向高位，进行运算，
 * 1. 设置循环边界
 * 2. 设置操作单位
 * 2.1. 把字符对应的ascii码标示的数字，相加，得到进位标志和结果数
 * 2.2. 结果数的处理
 * 2.3. 进位标志的处理，在长的字符中操作，因为长的字符串大于短的字符串，
 *    不会造成内存的越界访问
 * 3. 尾部处理 
 * @Param s1 string s1, length is bigger than s2
 * @Param s2
 * @Param len
 * @Param result
 *
 * @Returns   
 */
/* ----------------------------------------------------------------------------*/
int char_num_oper(elem_len_t *elems, char ** result){
    int ret = -1;
    int i;
    //default add result length by 1
    char * res_p =  (char *)malloc(elems->res_len + 1);
    if (res_p == NULL){
        *result = NULL;
        return ret;
    }
    memset(res_p, 0, elems->res_len);
    char zero = '0';
    int res_turn ; 
    for ( i = 0; i < elems->len2; i++){
        res_turn = elems->res_len  -i; 
        res_p[res_turn] += (elems->s1[elems->len1-i-1] + elems->s2[elems->len2 -i -1 ] - zero);
        //res_p[res_turn] += res_p[res_turn-1];
        if (res_p[res_turn] > '9'){
            res_p[res_turn] -= 10;
            res_p[res_turn-1] += 1;
        }
#ifdef DEBUG
        printf("result %d is %c\r\n", res_turn, res_p[res_turn]);
#endif
    }
    if ((elems->len1- elems->len2) > 0){
        res_turn--;
        while(res_turn > 0){
            res_p[res_turn] = res_p[res_turn]+elems->s1[res_turn-1];
            if (res_p[res_turn] > '9'){
                res_p[res_turn] -= 10;
                res_p[res_turn-1] += 1;
            }
#ifdef DEBUG
            printf("result %d is %c\r\n", res_turn, res_p[res_turn]);
#endif
            res_turn--;
        }
    }
    if(res_p[0] == 1){
        res_p[0] = '1';
    }
    *result = res_p;
    return 0;
}
int long_num_add(char *s1, char *s2, char ** result){
    int ret = -1;
    elem_len_t elems;
    ret = length_charge(s1, s2, &elems);
    switch(elems.type){
        case LEN_BOTH_ZERO:
            {
                *result = NULL;
                break;
            }
        case LEN_ONE_ZERO:
            {
                *result = elems.s1;
                ret = 0;
                break;
            }
        case LEN_NOT_EMPTY:
            {
                ret = char_num_oper(&elems, result);
                break;
            }
        default:
            *result = NULL;
    }
    return ret;
}

void result_print(char * result)
{
    int i = 0;
    int len = 0;
    if (result[0] == 0){
        i = 1;
        len = strlen(result+1);
    }else{
        len = strlen(result);
        i = 0;
    }
    printf("len %d, result:", len);
    for (; i< len+1; i++){
        printf("%c", result[i]);
    }
    printf("\r\n");

}

/* --------------------------------------------------------------------------*/
/**
 * @Synopsis  test function for long_num_add func
 *
 * @Param s1
 * @Param s2
 *
 * @Returns   
 */
/* ----------------------------------------------------------------------------*/
int two_num_add_test( char * s1, char *s2){
    char * result;
    int  res;
    res = long_num_add(s1, s2, &result);
    if (res == 0){
        result_print(result);
        free(result);
    }
    return 0;
}

/* --------------------------------------------------------------------------*/
/**
 * @Synopsis  输出N位数中的所有的数
 *            N=1，输出1-9
 *            N=2，输出1-99
 *            N=3  输出1-999
 * @Param n 位数
 *
 * @Returns   
 */
/* ----------------------------------------------------------------------------*/
int number_range_print(int n){
    int res;
    //get memory for store max number
    char * rel_result = (char *)malloc(n);
    memset(rel_result, '9', n);

    //
    char * const one = "1";
    char * one_tmp = "1";
    //one_tmp for proeventing oper_result change the one point
    //one variable shou be decorateing by const
    char ** oper_result = &one_tmp;
    //tmp for free unused memory space
    char * tmp = NULL;
    printf("len %d, result:%d\r\n", 1,1);

    res = long_num_add(one, *oper_result, oper_result); 
    if (res == 0){
        result_print(*oper_result);
    }

    while(1){
        tmp = *oper_result;
        //as operation func use strlen function, 
        //if oper_result first elems is zero, we should charge it
        //This find by gdb debug
        //TODO: create a result struct for avoid charge
        if(*oper_result[0] == 0 )
            res = long_num_add(one, *oper_result+1, oper_result); 
        else
            res = long_num_add(one, *oper_result, oper_result); 
        if (res == 0){
            result_print(*oper_result);
            if (tmp) free(tmp);
        }


        //end operation
        //if the result string is equal to max number string, stop
        //should charge the first byte of result
        //TODO:
        if(*oper_result[0] == 0 ){
            if (strcmp(*oper_result+1, rel_result) == 0){
                printf("end\r\n");
                break;
            }
        }else{
            if (strcmp(*oper_result, rel_result) == 0){
                printf("end\r\n");
                break;
            }
        }
    }
    //free the lase mem
    if (*oper_result) free(*oper_result);
}
int main(){
    char * s1 = "1234";
    char * s2 = "12345";
    two_num_add_test(s1, s2);
    s1 = "99";
    s2 = "9999";
    two_num_add_test(s1, s2);
    s1 = "913";
    s2 = "99802";
    two_num_add_test(s1, s2);
    number_range_print(1);

}
/* result
   len 5, result:13579
   len 5, result:10098
   len 6, result:100715
    len 1, result:1
    len 1, result:2
    len 1, result:3
    len 1, result:4
    len 1, result:5
    len 1, result:6
    len 1, result:7
    len 1, result:8
    len 1, result:9
   */
