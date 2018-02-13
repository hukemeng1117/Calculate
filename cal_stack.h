#ifndef _STACK_H_
#define _STACK_H_

#include "cal_base.h"

typedef struct _stackNode {
	calNode data;
	struct _stackNode* next;
}*pNode;

typedef struct _stack {
	pNode top;
	pNode bottom;
}*pStack;

/* init Stack  */
pStack initStack(void);

/* push Stack  */
bool pushStack(const pStack ps,const calNode data);

/* pop stack, pData 为NULL不会存储值*/
bool popStack(const pStack ps,calNode* pData);

/* search stack, index为返回查找结果*/
bool searchStack(const pStack ps,const calNode data, uint* index);

void transferStack(const pStack ps,void perform(calNode item) );

#endif /* stack_h */
