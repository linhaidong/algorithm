#include <stdio.h>
#include <stdlib.h>
#include <unistd.h> 
#include "fsm.h"
#include "action.h"
static int g_max_num;  //状态表里含有的状态个数
/*
 *当有事件到来时，
 1. 判断当前状态机的状态
 2. 根据当前的状态，找到设置的事件
 3. 调用触发函数
 4. 设置下一个状态
 * */
FsmTable_t XiaoMingTable[] =
{
	//{到来的事件，当前的状态，将要要执行的函数，下一个状态}
	{ EVENT1,  SLEEP,           GetUp,        GET_UP },
	{ EVENT2,  GET_UP,          Go2School,    GO_TO_SCHOOL },
	{ EVENT3,  GO_TO_SCHOOL,    HaveLunch,    HAVE_LUNCH },
	{ EVENT1,  HAVE_LUNCH,      DoHomework,   DO_HOMEWORK },
	{ EVENT2,  DO_HOMEWORK,     Go2Bed,       SLEEP },

	//add your codes here
};
char * event1_name = "good morning";
char * event2_name = "good afternoon";
char * event3_name = "good evenning";
char * event_no_name = "no event, error";

char * event_name_get(int event)
{
    char * p = NULL;
    switch(event){
        case EVENT1:
            p = event1_name;
            break;
        case EVENT2:
            p = event2_name;
            break;
        case EVENT3:
            p = event2_name;
            break;
        default:
            p = event_no_name;
    }
    return p;
}

/*状态机注册*/
void FSM_Regist(FSM_t* pFsm, FsmTable_t* pTable)
{
	pFsm->FsmTable = pTable;
}

int FSM_State_Get(FSM_t * fsm){
    return fsm->curState;
}
void FSM_StateTransfer(FSM_t* pFsm, int state)
{
	pFsm->curState = state;
}


/*事件处理*/
void FSM_EventHandle(FSM_t* pFsm, int event)
{
	FsmTable_t* pActTable = pFsm->FsmTable;
	void (*eventActFun)() = NULL;  //函数指针初始化为空
	int NextState;
	int CurState = pFsm->curState;
	int flag = 0; //标识是否满足条件

	/*获取当前动作函数*/
	for (int i = 0; i<g_max_num; i++)
	{
		//当前的状态和事件都匹配的时候，获取执行函数和下一个状态
        //设置标示
		if (event == pActTable[i].event && CurState == pActTable[i].CurState)
		{
			flag = 1;
			eventActFun = pActTable[i].eventActFun;
			NextState = pActTable[i].NextState;
			break;
		}
	}


	if (flag) //如果满足条件了
	{
		/*动作执行*/
		if (eventActFun)
		{
			eventActFun();
		}

		//跳转到下一个状态
		FSM_StateTransfer(pFsm, NextState);
	}
	else
	{
		// do nothing
        printf("fsm error,exit");
        exit(1);
	}
}


//初始化FSM
void InitFsm(FSM_t* pFsm)
{
	g_max_num = sizeof(XiaoMingTable) / sizeof(FsmTable_t);
	pFsm->curState = SLEEP;
	FSM_Regist(pFsm, XiaoMingTable);
}



