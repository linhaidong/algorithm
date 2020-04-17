/*************************************************************************
    > File Name: fsm.h
    > Author:     linhaidong
    > Mail:       linhaidong@alibaba-inc.com 
    > Time:      2020年04月17日 星期五 22时49分56秒
    > Abstract: 
 ************************************************************************/
#ifndef FSM_H
#define FSM_H

typedef  enum state
{
	GET_UP,
	GO_TO_SCHOOL,
	HAVE_LUNCH,
	DO_HOMEWORK,
	SLEEP,
}state_t;
//define event
typedef enum event
{
	EVENT1 = 1,
	EVENT2,
	EVENT3,
}event_t;
//define fsmtable
typedef struct FsmTable_s
{
	event_t event;   //事件
	state_t CurState;  //当前状态
	void (*eventActFun)();  //函数指针
	state_t NextState;  //下一个状态
}FsmTable_t;

//define state_machine
typedef struct FSM_s
{
	FsmTable_t* FsmTable;   //指向的状态表
    //a fsm only has one state at a time
	int curState;  //FSM当前所处的状态

}FSM_t;

extern void InitFsm(FSM_t* pFsm);
extern void FSM_Regist(FSM_t* pFsm, FsmTable_t* pTable);
extern void FSM_StateTransfer(FSM_t* pFsm, int state);
extern  void FSM_EventHandle(FSM_t* pFsm, int event);
extern char * event_name_get();
#endif
