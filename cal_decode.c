#include "cal_decode.h"
#include "cal_base.h"
#include "cal_math.h"
#include <string.h>
#include <stdlib.h>

//解码中有几个缺陷，大小写和空格，并且首位为-号或者+号无法处理，在这里预处理一下
char* stringPreHandle(char* string) {
    char* tempString = (char*)malloc(MAX_LENGTH + 1);
    memset(tempString, MAX_LENGTH, 0);
    ulong index = 0;
    
    for(ulong i = 0;i<strlen(string) && index < MAX_LENGTH;i++) {
        if(string[i] >= 'A' && string[i] <= 'Z') {
            //大写转小写
            tempString[index++] = string[i] - 'A' + 'a';
        } else if(string[i] == ' ') {
            //去除空格
            continue;
        } else if(i == 0 || string[i] == '(' || string[i] == ',') {
            if(string[i] == '-') {
                tempString[index++] = '0';
                tempString[index++] = '-';
            } else if (string[i] == '+') {
                continue;
            } else {
                tempString[index++] = string[i] ;
            }
            
        } else {
            tempString[index++] = string[i];
        }
    }
    tempString[index] = '\0';
    return tempString;
}

CAL_TYPE decodeType(const char c) {
	
	if((c >= '0' && c <= '9') || c == '.') {
		return CAL_NUMBER;
	}
	else if(c == '(' || c == ')') {
		return CAL_BRACKET;
	}
    else if(c == ',') {
        return CAL_PUNCK;
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
bool decodeString(char* str) {
	ASSERT_RETURN(str != NULL, false);
	
	
	uint decodeLength = 0;
	calNode data;
    
    char* string = stringPreHandle(str);
    ulong maxLength = strlen(string);
    
	while(*(string + decodeLength) != '\0') {
		
		data.calType = decodeType(string[decodeLength]);

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
        
        else if(data.calType == CAL_PUNCK) {
            decodeLength += 1;
        }
        
        if(!mathProcCalNode(&data)) {
            ASSERT_RETURN(0, false);
        }
		ASSERT_RETURN(decodeLength <= maxLength, false);
	}
    
    //已经结束，对结束的处理
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

