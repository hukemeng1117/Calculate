#ifndef _CBASE_H_
#define _CBASE_H_

#include <assert.h>
#include <stdio.h>

#define IN
#define OUT

#define  uint unsigned int
#define  udouble unsigned double
#define  ushort unsigned short

#define bool int
#define false 0
#define true 1

#define ASSERT_RETURN(condition) \
do { \
	if(!(condition)) {\
		assert(0); \
		return;\
	}\
}while(0) \

#define ASSERT_RETURN(condition,value) \
do { \
	if(!(condition)) { \
		assert(0); \
		return value;\
	}\
}while(0) \

typedef enum _CAL_TYPE{
	CAL_NUMBER,   //数值
	CAL_OPERATE,  // 运算符
	CAL_BRACKET,  // 括号符
	CAL_PUNCK,   // 标点符
}CAL_TYPE;

typedef struct _cal_Node {
	union {
		double value;  //数字
		int operater;  //运算操作
		char bracket;  //
		char punck;
	};
	CAL_TYPE calType;
}calNode;


bool cal_compare(const calNode* node1,const calNode* node2);

#endif




