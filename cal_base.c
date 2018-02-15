#include "cal_base.h"
#include <string.h>

cal_operater_node g_calOperationList[OP_ERROR] = {
    {
        1,  "+",
    },
    {
        1,  "-",
    },
    {
        2,  "*",
    },
    {
        2,  "/",
    },
    {
        3,  "^",
    },
    {
        3,  "%",
    },
};


cal_operater_node* getCalOperationDesc(CAL_OPERATOR_TYPE op) {
    ASSERT_RETURN(op < OP_ERROR, NULL);
    return &g_calOperationList[op];
}

bool cal_compare(const calNode* node1,const calNode* node2) {
	if(node1->calType != node1->calType) {
		return false;
	}
	if(node1->calType == CAL_NUMBER && node1->value == node2->value) {
		return true;
	}
	else if(node1->calType == CAL_OPERATE && node1->operater == node2->operater) {
		return true;
	}
	else if(node1->calType == CAL_BRACKET && node1->bracket == node2->bracket) {
		return true;
	}
	else if(node1->calType == CAL_PUNCK && node1->punck == node2->punck) {
		return true;
	}
	return false;
}

bool cal_strcmp(const char* str1,const char* str2,const ulong length) {
	ASSERT_RETURN(strlen(str1) >= length && strlen(str2) >= length, false);
	for(int i = 0;i<length;i++) {
		if(str1[i] != str2[i]) {
			return false;
		}
	}
	return true;
}
