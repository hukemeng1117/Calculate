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

ulong getStackDepth(const pStack ps) {
    ASSERT_RETURN(ps != NULL, false);
    ASSERT_RETURN(ps->top != NULL,false);
    pNode tempNode = ps->top;
    ulong length = 0;
    
    while(tempNode != NULL && tempNode != ps->bottom) {
        length ++;
        tempNode = tempNode->next;
    }
    return length;
}

bool clearStack(const pStack ps) {
    ASSERT_RETURN(ps != NULL, false);
    ASSERT_RETURN(ps->top != NULL,false);
    pNode tempNode = ps->top;
    
    while(tempNode != NULL && tempNode != ps->bottom) {
        ps->top = ps->top->next;
        free(tempNode);
        tempNode = ps->top;
    }
    return true;
}

pNode searchStack(const pStack ps,int condition(pNode node)) {
	ASSERT_RETURN(ps != NULL, false);
	ASSERT_RETURN(ps->top != NULL,false);
	pNode tempNode = ps->top;

	do {
        int ret = condition(tempNode);
        if(ret == CONTINUE)
            tempNode = tempNode->next;
        else if(ret == RETURN)
            return tempNode;
        else if(ret == BREAK)
            break;
	}while(tempNode != NULL && tempNode != ps->bottom);
	return NULL;
}

void transferStack(const pStack ps,void perform(calNode item) ) {
	pNode tempNode = ps->top;
	while(tempNode != ps->bottom) {
		perform (tempNode->data);
		tempNode = tempNode->next;
	}
	printf("\n");
}
