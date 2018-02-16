#include "cal_decode.h"
#include "cal_base.h"
#include "cal_math.h"
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
	calNode data;
	
	while(*(string + decodeLength) != '\0') {
		
		data.calType = decodeType(string[decodeLength]);
		ASSERT_RETURN(data.calType != CAL_ERROR, false);
		if(data.calType == CAL_NUMBER) {
			data.value = decodeNumber(string + decodeLength, &decodeLength);
		}
        
        else if(data.calType == CAL_OPERATE) {
            data.operater = decodeOperator(string + decodeLength, &decodeLength);
            ASSERT_RETURN(data.operater != OP_ERROR, false);
        }
        
        else if(data.calType == CAL_BRACKET) {
            data.bracket = *(string + decodeLength);
            decodeLength += 1;
        }
        if(!mathProcCalNode(&data)) {
            ASSERT_RETURN(0, false);
        }
		ASSERT_RETURN(decodeLength <= maxLength, false);
	}
    
    data.calType = CAL_END;
    if(!mathProcCalNode(&data)) {
        ASSERT_RETURN(0, false);
    }
	return true;
}

bool decodeResult(double* result) {
    ASSERT_RETURN(mathGetValue(result), false);
    return true;
}

