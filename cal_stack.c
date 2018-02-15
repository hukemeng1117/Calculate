#include "cal_base.h"
#include "cal_stack.h"
#include <stdlib.h>

pStack initStack(void) {
	pStack ps;
	if((ps = (pStack)malloc(sizeof(struct _stack))) == NULL) {
		ASSERT_RETURN(0,NULL);
	}
	if((ps->bottom = (pNode)malloc(sizeof(struct _stackNode))) == NULL) {
		ASSERT_RETURN(0,NULL);
	}
	ps->top = ps->bottom;
	return ps;
}

bool pushStack(const pStack ps,const calNode data) {
	ASSERT_RETURN(ps != NULL,false);
	
	pNode tempNode = (pNode)malloc(sizeof(struct _stackNode));
	ASSERT_RETURN(tempNode != NULL,false);
	tempNode->next = ps->top;
	tempNode->data = data;
	
	ps->top = tempNode;
	return true;
}

bool popStack(const pStack ps,calNode* pData) {
	ASSERT_RETURN(ps != NULL,false);
	ASSERT_RETURN(ps->top != NULL && ps->top != ps->bottom,false);
	
	pNode temp = ps->top;
	ps->top = ps->top->next;
	
	if(pData != NULL) {
		*pData = temp->data;
	}
	free(temp);
	return true;
}

bool searchStack(const pStack ps,const calNode data, uint* index) {
	ASSERT_RETURN(ps != NULL && index != NULL, false);
	ASSERT_RETURN(ps->top != NULL && ps->top != ps->bottom,false);
	pNode tempNode = ps->top;
	
	uint tempIndex = 0;
	do {
		if(cal_compare(&(tempNode->data),&data)) {
			*index = tempIndex;
			return true;
		}
		tempIndex ++;
		tempNode = tempNode->next;
	}while(tempNode != NULL && tempNode != ps->bottom);
	return false;
}

void transferStack(const pStack ps,void perform(calNode item) ) {
	pNode tempNode = ps->top;
	while(tempNode != ps->bottom) {
		perform (tempNode->data);
		tempNode = tempNode->next;
	}
	printf("\n");
}
