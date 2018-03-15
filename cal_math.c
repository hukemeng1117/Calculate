//
//  cal_math.c
//  Calculate


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
    
    if(data.calType == CAL_PUNCK) {
        printf(", ");
    }
}

//向栈的底部查找前一个操作符，如果查到括号或者逗号则停止，查到运算操作返回
int serchOperator(pNode node) {
    ASSERT_RETURN(node != NULL, BREAK);
    //寻找操作符
    if((node->data).calType == CAL_BRACKET || (node->data).calType == CAL_PUNCK)
        return BREAK;
    if((node->data).calType == CAL_OPERATE)
        return RETURN;
    return CONTINUE;
}

pStack math_pStack = NULL;

double sum(double* datas,uint length) {
    double temp = 0.0;
    for(int index = 0;index < length;index ++ ) {
        temp += datas[index];
    }
    return temp;
}

double varp(double* datas,uint length) {
    double tempAvg = sum(datas,length) / length;
    double tempSum = 0.0;
    for(int i = 0;i < length;i++) {
        tempSum += pow (datas[i] - tempAvg,2);
    }
    return tempSum / length;
}

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
//一个参数的函数运算
bool mathProcFunctionCalculate(double data,CAL_OPERATOR_TYPE op,double* value) {
    switch (op) {
        case OP_SIN:
            *value = sin(data / 180 * MATH_PI);
            break;
        case OP_COS:
            *value = sin(data / 180 * MATH_PI);
            break;
        case OP_TAN:
            *value = cos(data / 180 * MATH_PI);
            break;
        case OP_SINH:
            *value = sinh(data / 180 * MATH_PI);
            break;
        case OP_TANH:
            *value = sinh(data / 180 * MATH_PI);
            
            break;
        case OP_COSH:
            *value = sinh(data / 180 * MATH_PI);
            break;
        case OP_LOG10:
            *value = log10(data);
            break;
        case OP_LN:
            *value = log(data);
            break;
        default:
            ASSERT_RETURN(0, false);
    }
    return true;
}

//多个参数的函数的运算，将结果存储到datas第0位
bool mathProcFunctionCalculateByList(double* datas,uint length,CAL_OPERATOR_TYPE op) {
    ASSERT_RETURN(length > 0 && datas != NULL, false);
    if(op == OP_POW) {
        ASSERT_RETURN(length == 2, false);
        *datas = pow(datas[1], datas[0]);
    }
    else if(op == OP_SUM) {
        *datas = sum(datas, length);
    }
    else if(op == OP_LOG) {
        ASSERT_RETURN(length == 2, false);
        *datas = log(datas[0]) / log(datas[1]);
    } else if(op == OP_AVG) {
        *datas = sum(datas,length) / length;
    } else if(op == OP_VARP) {
        *datas = varp(datas,length);
    }
    else{
        ASSERT_RETURN(0, false);
    }
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
    
    //普通函数运算  sin cos
    else if(calOpInfo->level == 4) {
        ASSERT_RETURN(mathProcFunctionCalculate(data1,op,&(pushData.value)),false);
    }
    
    pushData.calType = CAL_NUMBER;
    pushStack(math_pStack, pushData);
    
    return true;
}

//去除前一个括号
bool mathProcBranket() {
    calNode popData;
    calNode pushData;
    double datas[64];
    bool punckFlag = false;
    uint index = 1;
    
    ASSERT_RETURN(popStack(math_pStack, &popData), false);
    ASSERT_RETURN(popData.calType == CAL_NUMBER, false);
    datas[0] = popData.value;
    
    //取出数据，直到取出前括号
    do {
        ASSERT_RETURN(popStack(math_pStack, &popData), false);
        if(popData.calType == CAL_BRACKET) {
           ASSERT_RETURN(popData.bracket == '(', false);
        }
        
        //如果当前此节点存储的为逗号，则再次出栈，取出数据,并且要取出括号前的函数，将punckFlag置位1
        else if(popData.calType == CAL_PUNCK) {
            punckFlag = true;
            
            ASSERT_RETURN(popStack(math_pStack, &popData), false);
            ASSERT_RETURN(popData.calType == CAL_NUMBER, false);
            datas[index ++] = popData.value;
        } else {
            ASSERT_RETURN(0, false);
        }
    }while(popData.calType != CAL_BRACKET);
    
    if(punckFlag) {
        ASSERT_RETURN(popStack(math_pStack, &popData), false);
        ASSERT_RETURN(popData.calType == CAL_OPERATE, false);
        ASSERT_RETURN(mathProcFunctionCalculateByList(datas,index,popData.operater),false);
    }
    pushData.calType = CAL_NUMBER;
    pushData.value = datas[0];
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
        if(data->bracket == '(') {
            ASSERT_RETURN(pushStack(math_pStack, *data),false);
        } else if(data->bracket == ')') {
            while(searchStack(math_pStack, serchOperator) != NULL) {
                ASSERT_RETURN(mathProcOperate(), false);
            }
            ASSERT_RETURN(mathProcBranket(), false);
        } else {
            ASSERT_RETURN(0, false);
        }
        
    }
    
    else if(data->calType == CAL_PUNCK) {
        while(searchStack(math_pStack, serchOperator) != NULL) {
            ASSERT_RETURN(mathProcOperate(), false);
        }
        pushStack(math_pStack, *data);
    }
    
    else if(data->calType == CAL_END) {
        while(searchStack(math_pStack, serchOperator) != NULL) {
            ASSERT_RETURN(mathProcOperate(), false);
        }
    }
    return true;
}

bool mathGetValue(double* result) {
    ASSERT_RETURN(result != NULL, false);
    if(getStackDepth(math_pStack) != 1) {
        clearStack(math_pStack);
        ASSERT_RETURN(0, false);
    }
    
    calNode popData;
    ASSERT_RETURN(popStack(math_pStack, &popData), false);
    ASSERT_RETURN(popData.calType == CAL_NUMBER, false);
    *result = popData.value;
    
    return true;
}

