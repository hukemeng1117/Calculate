#include "cal_decode.h"
#include "cal_base.h"
#include <string.h>

CAL_TYPE decodeType(const char c) {
	
	if((c >= '0' && c <= '9') || c == '.') {
		return CAL_NUMBER;
	}
	if(c == '(' || c == ')' || c == '[' || c == ']') {
		return CAL_BRACKET;
	}
	return CAL_OPERATE;
}

CAL_OPERATOR_TYPE decodeOperator(const char* start,uint* index) {
	ulong maxLength = strlen(start);
	for(uint op = 0; op < OP_ERROR;op++)  {
		
        cal_operater_node* opList = getCalOperationDesc(op);
		ulong opLength = strlen(opList->opeDesprition);
		if(opLength > maxLength) {
			continue;
		}
		if(cal_strcmp(start,opList->opeDesprition,opLength)) {
            *index = (uint)opLength + (*index);
            return op;
		}
	}
	return OP_ERROR;
}

double decodeNumber(const char* start,uint* index) {
	ASSERT_RETURN(start != NULL && index != NULL, 0.0);
	double Interger = 0.0;
	double Pointer = 0.0;
	for(; *start != '\0' && *start >= '0' && *start <= '9'; start++) {
		Interger = Interger * 10 + *start - '0';
		(*index)++;
	}
	if(*start != '.') {
		return Interger;
	}
	start ++;
	(*index)++;
	
	double pointPow = 0.1;
	
	for(; *start != '\0' && *start >= '0' && *start <= '9'; start++) {
		Pointer = Pointer + (*start - '0') * pointPow;
		pointPow *= 0.1;
		(*index)++;
	}
	
	return Interger + Pointer;
}
//解码成功返回true
bool decodeString(const char* string) {
	ASSERT_RETURN(string != NULL, false);
	
	ulong maxLength = strlen(string);
	uint decodeLength = 0;
	calNode node;
	
	while(*(string + decodeLength) != '\0') {
		
		node.calType = decodeType(string[decodeLength]);
		ASSERT_RETURN(node.calType != CAL_ERROR, false);
		
		if(node.calType == CAL_NUMBER) {
			node.value = decodeNumber(string + decodeLength, &decodeLength);
            printf("%f\n",node.value);
		}
        
        if(node.calType == CAL_OPERATE) {
            node.operater = decodeOperator(string + decodeLength, &decodeLength);
            ASSERT_RETURN(node.operater != OP_ERROR, false);
            printf("%s\n",getCalOperationDesc(node.operater)->opeDesprition);
        }
        
        if(node.calType == CAL_BRACKET) {
            node.bracket = *(string + decodeLength);
            decodeLength += 1;
            printf("%c\n",node.bracket);
        }
		ASSERT_RETURN(decodeLength <= maxLength, false);
	}
	return true;
}
