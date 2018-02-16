#include <stdio.h>
#include "cal_decode.h"
#include <math.h>

void test1() {
    char* string = "+123.001-238432+11/23+21367+213*34/4^1.1";
    double result;
    if(decodeString(string) && decodeResult(&result)) {
        double expect = -215365.389;
        printf("string: %s\r\nvalue: %f \r\nexpect: %f\n\n",string,result,expect);
    } else {
        printf("string: %s\r\nfailed",string);
    }
}

void test2() {
    char* string = "123.001+238432+11*23+(21367+213)*34/4^1.1";
    double result;
    if(decodeString(string) && decodeResult(&result)) {
        double expect = 398493.091;
        printf("string: %s\r\nvalue: %f \r\nexpect: %f\n\n",string,result,expect);
    } else {
        printf("string: %s\r\nfailed",string);
    }
}

void test3() {
    char* string = "9%4.4^1.54*98435-359+(3248*(2219.212-248)/(2148-237.76765))^2.2";
    double result;
    if(decodeString(string) && decodeResult(&result)) {
        double expect = 56969072.8;
        printf("string: %s\r\nvalue: %f \r\nexpect: %f\n\n",string,result,expect);
    } else {
        printf("string: %s\r\nfailed",string);
    }
}

void test4() {
    char* string = "+sin(45)+cos(24)-tan(55)";
    double result;
    if(decodeString(string) && decodeResult(&result)) {
        double expect = 0.192504232;
        printf("string: %s\r\nvalue: %f \r\nexpect: %f\n\n",string,result,expect);
    } else {
        printf("string: %s\r\nfailed",string);
    }
}

void test5() {
    char* string = "cos(24*325)+tan(24)-1294.43643*(1+2.1^(1.1+1.7))";
    double result;
    if(decodeString(string) && decodeResult(&result)) {
        double expect = -11629.1169;
        printf("string: %s\r\nvalue: %f \r\nexpect: %f\n\n",string,result,expect);
    } else {
        printf("string: %s\r\nfailed",string);
    }
}

void test6() {
    char* string = "pow(2*6,3^1.7)";
    double result;
    if(decodeString(string) && decodeResult(&result)) {
        double expect = 9672721.12;
        printf("string: %s\r\nvalue: %f \r\nexpect: %f\n\n",string,result,expect);
    } else {
        printf("string: %s\r\nfailed",string);
    }
}

void test7() {
    char* string = "sum(pow(2*6,3^1.7),12834*127)";
    double result;
    if(decodeString(string) && decodeResult(&result)) {
        double expect = 11302639.1;
        printf("string: %s\r\nvalue: %f \r\nexpect: %f\n\n",string,result,expect);
    } else {
        printf("string: %s\r\nfailed",string);
    }
}

int main(int argc, char *argv[]) {
    test1();
    test2();
    test3();
    test4();
    test5();
    test6();
    test7();
}
