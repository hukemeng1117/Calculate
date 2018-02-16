#ifndef _CAL_BASE_H_
#define _CAL_BASE_H_

#include <stdio.h>

#define  uint unsigned int
#define  udouble unsigned double
#define  ushort unsigned short
#define  ulong unsigned long

#define bool int
#define false 0
#define true 1

#define CONTINUE 0
#define BREAK 1
#define RETURN 2

#define ASSERT_RETURN(condition) \
do { \
	if(!(condition)) {\
		printf("%s [%s : %d]\r\n",__FUNCTION__,__FILE__,__LINE__); \
		return;\
	}\
}while(0) \

#define ASSERT_RETURN(condition,value) \
do { \
	if(!(condition)) { \
		printf("ASSERT: %s [%s : %d]\r\n",__FUNCTION__,__FILE__,__LINE__); \
		return value;\
	}\
}while(0) \

typedef enum _CAL_TYPE{
	CAL_NUMBER,   //数值
	CAL_OPERATE,  // 运算符
	CAL_BRACKET,  // 括号符
	CAL_END,   // 结束符
	CAL_ERROR,  //错误码
}CAL_TYPE;

typedef enum _cal_operater_type {
    OP_ADD,
    OP_PLUS,
    OP_MULTIPLY,
    OP_DIVISE,
    OP_INVOLUTION,
    OP_MOD,
    
    OP_ERROR,
}CAL_OPERATOR_TYPE;

typedef struct _cal_Node {
	union {
		double value;  //数字
		CAL_OPERATOR_TYPE operater;  //运算操作
		char bracket;  //
		char punck;
	};
	CAL_TYPE calType;
}calNode;



typedef struct _cal_operater_node {
	uint level;   //运算等级
	char* opeDesprition;  //运算描述
}cal_operater_node;


cal_operater_node* getCalOperationDesc(CAL_OPERATOR_TYPE op);
bool cal_compare(const calNode* node1,const calNode* node2);
bool cal_strcmp(const char* str1,const char* str2,const ulong length);

#endif




