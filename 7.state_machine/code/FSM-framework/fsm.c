#include <stdio.h>
#include <stdlib.h>
#include <unistd.h> 
#include "fsm.h"
#include "action.h"
static int g_max_num;  //״̬���ﺬ�е�״̬����
/*
 *�����¼�����ʱ��
 1. �жϵ�ǰ״̬����״̬
 2. ���ݵ�ǰ��״̬���ҵ����õ��¼�
 3. ���ô�������
 4. ������һ��״̬
 * */
FsmTable_t XiaoMingTable[] =
{
	//{�������¼�����ǰ��״̬����ҪҪִ�еĺ�������һ��״̬}
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

/*״̬��ע��*/
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


/*�¼�����*/
void FSM_EventHandle(FSM_t* pFsm, int event)
{
	FsmTable_t* pActTable = pFsm->FsmTable;
	void (*eventActFun)() = NULL;  //����ָ���ʼ��Ϊ��
	int NextState;
	int CurState = pFsm->curState;
	int flag = 0; //��ʶ�Ƿ���������

	/*��ȡ��ǰ��������*/
	for (int i = 0; i<g_max_num; i++)
	{
		//��ǰ��״̬���¼���ƥ���ʱ�򣬻�ȡִ�к�������һ��״̬
        //���ñ�ʾ
		if (event == pActTable[i].event && CurState == pActTable[i].CurState)
		{
			flag = 1;
			eventActFun = pActTable[i].eventActFun;
			NextState = pActTable[i].NextState;
			break;
		}
	}


	if (flag) //�������������
	{
		/*����ִ��*/
		if (eventActFun)
		{
			eventActFun();
		}

		//��ת����һ��״̬
		FSM_StateTransfer(pFsm, NextState);
	}
	else
	{
		// do nothing
        printf("fsm error,exit");
        exit(1);
	}
}


//��ʼ��FSM
void InitFsm(FSM_t* pFsm)
{
	g_max_num = sizeof(XiaoMingTable) / sizeof(FsmTable_t);
	pFsm->curState = SLEEP;
	FSM_Regist(pFsm, XiaoMingTable);
}



