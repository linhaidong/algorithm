/*************************************************************************
    > File Name: list.c
    > Author:     linhaidong
    > Mail:       linengier@126.com
    > Time:      Mon Apr  1 05:08:22 2019
    > Abstract: 
 ************************************************************************/
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
typedef struct list {
    
    int data;
    struct list * next;
}list;


list * list_init(int data){
    list * head;
    head = (list *)malloc(sizeof(list));
    if (head == NULL){
        return NULL;
    }
    head->next = NULL;
    head->data =  data;
    return head;
}

int  insert(list * head, int data)
{
    if (head == NULL){
        return -1;
    }
    list *p = (struct list *)malloc(sizeof(list));
    if ( p == NULL ){
        return -1;
    }
    p->data =  data;
    //p->next = head->next;
    p->next = NULL;
    while(head->next){
        head = head->next;
    }
    head->next = p;
    return 0;
}

int print_list(struct list * head){
    while(head){
        printf("data is %d\r\n", head->data);
        head = head->next;
    }
    printf("\r\n");
    return 0;
}

int free_list(struct list * head){
    
    while(head != NULL){
        list * next = head->next;
        free(head);
        head =  next;
    }
    return 0;
}



list *  invert_list(list * head){
    if(head == NULL || head->next == NULL){
        return head;
    }
    list *pre = NULL, *next = NULL;
    while(head){
      //保留下一个指针
      next = head->next;
      //反转
      head->next=  pre;
      //记录上一个指针
      pre =  head;
      head = next;
    }
    return pre;
        
}


list * recovery_list(list * head){
    if (head == NULL || head->next == NULL){
        return head;
    }
    list *node =  recovery_list(head->next);
    printf("head data is %d\r\n", head->data);
    head->next->next=head;
    head->next = NULL;
    return node;
}
int main(){
    list * head;
    head = list_init(0);
    if (head == NULL){
        return -1;
    }
    insert(head, 1);
    insert(head, 2);
    insert(head, 3);
    insert(head, 4);
    insert(head, 5);
    print_list(head);
    //head = invert_list(head);
    head = recovery_list(head);
    print_list(head);
    free_list(head);
}
