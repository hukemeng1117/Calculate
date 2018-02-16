//
//  cal_math.c
//  Calculate
//
//  Created by 尚立 on 2018/2/15.
//  Copyright © 2018年 尚立. All rights reserved.
//

#include "cal_math.h"
#include "cal_base.h"
#include "cal_stack.h"
#include <math.h>

void println(calNode data) {
    if(data.calType == CAL_NUMBER) {
        printf("%f  ",data.value);
    }
    
    if(data.calType == CAL_OPERATE) {
        cal_operater_node* opInfo = getCalOperationDesc(data.operater);
        printf("%s  ",opInfo->opeDesprition);
    }
}

//向栈的底部查找前一个操作符，如果查到括号或者逗号则停止，查到运算操作返回
int serchOperator(pNode node) {
    ASSERT_RETURN(node != NULL, BREAK);
    //寻找操作符
    if((node->data).calType == CAL_BRACKET)
        return BREAK;
    if((node->data).calType == CAL_OPERATE)
        return RETURN;
    return CONTINUE;
}


pStack math_pStack = NULL;

bool mathProcBaseCaculate(double data1,double data2,CAL_OPERATOR_TYPE op,double* value) {
    if(op == OP_ADD)
        *value = data1 + data2;
    
    else if(op == OP_PLUS)
        *value = data2 - data1;
    
    else if(op == OP_MULTIPLY)
        *value = data1 * data2;
    
    else if(op == OP_DIVISE) {
        if(data1 != 0.0) {
            *value = data2 / data1;
        } else {
            return false;
        }
    }
    
    else if(op == OP_INVOLUTION)
        *value = pow(data2,data1);
    
    else if(op == OP_MOD) {
        if(data2 != 0.0) {
            *value = data2- (ulong)(data2 / data1) * data1;
        } else {
            return false;
        }
    }
    
    return true;
}

bool mathProcFunctionCalculate(double data,CAL_OPERATOR_TYPE op,double* value) {
    if(op == OP_SIN)
        //弧度转化成角度
        *value = sin(data / 180 * MATH_PI);
    else if(op == OP_COS)
        *value = cos(data / 180 * MATH_PI);
    else if(op == OP_TAN)
        *value = tan(data / 180 * MATH_PI);
    else
        ASSERT_RETURN(0, false);
    return true;
}

bool mathProcOperate() {
    calNode popData;
    calNode pushData;
    
    double data1 = 0.0,data2 = 0.0;
    CAL_OPERATOR_TYPE op = OP_ERROR;
    
    ASSERT_RETURN(popStack(math_pStack, &popData), false);
    ASSERT_RETURN(popData.calType == CAL_NUMBER, false);
    data1 = popData.value;
    
    ASSERT_RETURN(popStack(math_pStack, &popData), false);
    ASSERT_RETURN(popData.calType == CAL_OPERATE, false);
    ASSERT_RETURN(popData.operater != OP_ERROR, false);
    op = popData.operater;
    
    cal_operater_node* calOpInfo = getCalOperationDesc(op);
    //基本运算
    if(calOpInfo->level <= 3) {
        ASSERT_RETURN(popStack(math_pStack, &popData), false);
        ASSERT_RETURN(popData.calType == CAL_NUMBER, false);
        data2 = popData.value;
        ASSERT_RETURN(mathProcBaseCaculate(data1,data2,op,&(pushData.value)), false);
    }
    
    //函数运算
    else if(calOpInfo->level == 4) {
        ASSERT_RETURN(mathProcFunctionCalculate(data1,op,&(pushData.value)),false);
    }
    
    pushData.calType = CAL_NUMBER;
    pushStack(math_pStack, pushData);
    
    return true;
}

//去除前一个括号
bool mathProcBranket(char branket) {
    calNode popData;
    calNode pushData;
    double data;
    
    ASSERT_RETURN(popStack(math_pStack, &popData), false);
    ASSERT_RETURN(popData.calType == CAL_NUMBER, false);
    data = popData.value;
    
    ASSERT_RETURN(popStack(math_pStack, &popData), false);
    ASSERT_RETURN(popData.calType == CAL_BRACKET, false);
    
    if(branket == ')') {
        ASSERT_RETURN(popData.bracket == '(', false);
    } else if(branket == ']') {
        ASSERT_RETURN(popData.bracket == '[', false);
    } else {
        ASSERT_RETURN(0, false);
    }
    
    pushData.calType = CAL_NUMBER;
    pushData.value = data;
    ASSERT_RETURN(pushStack(math_pStack, pushData), false);
    
    return true;
}

bool mathProcCalNode(const calNode* data){
    ASSERT_RETURN(data != NULL, false);
    if(math_pStack == NULL) {
        math_pStack = initStack();
    }

    if(data->calType == CAL_NUMBER) {
        pushStack(math_pStack, *data);
    }
    else if(data->calType == CAL_OPERATE) {
        pNode temppNode = NULL;
        cal_operater_node* operatorInfo = getCalOperationDesc(data->operater);
        while((temppNode = searchStack(math_pStack, serchOperator)) != NULL) {
            cal_operater_node* tempOperatoerInfo = getCalOperationDesc((temppNode->data).operater);
            //如果之前节点的优先级小于或者等于当前节点的优先级，则可以进行出栈操作
            if(tempOperatoerInfo->level >= operatorInfo->level) {
                if(!mathProcOperate()) {
                    return false;
                }
            } else {
                break;
            }
        }
        pushStack(math_pStack, *data);
    }
    else if(data->calType == CAL_BRACKET) {
        if(data->bracket == '(' || data->bracket == '[') {
            pushStack(math_pStack, *data);
        } else if(data->bracket == ')' || data->bracket == ']') {
            while(searchStack(math_pStack, serchOperator) != NULL) {
                ASSERT_RETURN(mathProcOperate(), false);
            }
            ASSERT_RETURN(mathProcBranket(data->bracket), false);
        } else {
            ASSERT_RETURN(0, false);
        }
        
    }
    
    else if(data->calType == CAL_END) {
        while(searchStack(math_pStack, serchOperator) != NULL) {
            ASSERT_RETURN(mathProcOperate(), false);
        }
    }
//    transferStack(math_pStack, println);
    return true;
}

bool mathGetValue(double* result) {
    ASSERT_RETURN(result != NULL, false);
    if(getStackDepth(math_pStack) != 1) {
        clearStack(math_pStack);
        ASSERT_RETURN(0, false);
    }
    ASSERT_RETURN(getStackDepth(math_pStack) == 1, false);
    
    calNode popData;
    ASSERT_RETURN(popStack(math_pStack, &popData), false);
    ASSERT_RETURN(popData.calType == CAL_NUMBER, false);
    *result = popData.value;
    
    return true;
}

