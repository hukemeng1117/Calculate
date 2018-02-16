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

//向栈的底部查找前一个操作符，如果查到括号则停止，查到运算操作返回
int serchOperator(pNode node) {
    ASSERT_RETURN(node != NULL, BREAK);
    //寻找操作符
    if((node->data).calType == CAL_BRACKET)
        return BREAK;
    if((node->data).calType == CAL_OPERATE)
        return RETURN;
    return CONTINUE;
}

pStack math_pStack;

bool mathProcCaculate(double data1,double data2,CAL_OPERATOR_TYPE op,double* value) {
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

void println(calNode data) {
    if(data.calType == CAL_NUMBER) {
        printf("%f  ",data.value);
    }
    
    if(data.calType == CAL_OPERATE) {
        cal_operater_node* opInfo = getCalOperationDesc(data.operater);
        printf("%s  ",opInfo->opeDesprition);
    }
}

bool mathProcOperate() {
    calNode popData;
    double data1 = 0.0,data2 = 0.0;
    CAL_OPERATOR_TYPE op = OP_ERROR;
    
    if(popStack(math_pStack, &popData)) {
        ASSERT_RETURN(popData.calType == CAL_NUMBER, false);
        data1 = popData.value;
    } else {
        ASSERT_RETURN(0, false);
    }
    
    if(popStack(math_pStack, &popData)) {
        ASSERT_RETURN(popData.calType == CAL_OPERATE, false);
        ASSERT_RETURN(popData.operater != OP_ERROR, false);
        op = popData.operater;
    } else {
        ASSERT_RETURN(0, false);
    }
    
    if(popStack(math_pStack, &popData)) {
        ASSERT_RETURN(popData.calType == CAL_NUMBER, false);
        data2 = popData.value;
    } else {
        ASSERT_RETURN(0, false);
    }
    
    calNode pushData;
    if(mathProcCaculate(data1,data2,op,&(pushData.value)) == false) {
        ASSERT_RETURN(0, false);
    }
    pushData.calType = CAL_NUMBER;
    pushStack(math_pStack, pushData);
    
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
        pushStack(math_pStack, *data);
    }
    
    else if(data->calType == CAL_END) {
        while(searchStack(math_pStack, serchOperator) != NULL) {
            ASSERT_RETURN(mathProcOperate(), false);
            transferStack(math_pStack, println);
        }
    }
    transferStack(math_pStack, println);
//    println(math_pStack->top->data);
    return true;
}

