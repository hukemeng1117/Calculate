#include <stdio.h>
#include "cal_stack.h"

void *print(calNode node) {
	if(node.calType == CAL_NUMBER) {
		printf("%f ",node.value);
	}
}


int main(int argc, char *argv[]) {
	calNode node1 = {4.5,CAL_NUMBER};
	calNode node2 = {1,CAL_OPERATE};
	calNode node3 = {1,CAL_NUMBER};
	
	pStack ps = initStack();
	pushStack(ps, node1);
	pushStack(ps, node2);
	pushStack(ps, node3);
	pushStack(ps, node1);
	pushStack(ps, node2);
	pushStack(ps, node3);
	
	transferStack(ps, print);
}