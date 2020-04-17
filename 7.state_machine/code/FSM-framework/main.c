/*************************************************************************
    > File Name: main.c
    > Author:     linhaidong
    > Mail:       linhaidong@alibaba-inc.com 
    > Time:      2020年04月17日 星期五 22时49分19秒
    > Abstract: 
 ************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "fsm.h"
void test(int *event)
{
	if (*event == 3)
	{
		*event = 1;
	}
	else
	{
		(*event)++;
	}
	
}

int main()
{
	FSM_t fsm;
	InitFsm(&fsm);
	int event = EVENT1; 
	while (1)
	{
		printf("event %s is coming...\n", event_name_get(event));
		FSM_EventHandle(&fsm, event);
		printf("fsm current state %d\n", fsm.curState);
		test(&event); 
		sleep(1);  //休眠1秒，方便观察
	}

	return 0;
}
