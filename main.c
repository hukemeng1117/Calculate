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
    char* string = "COS(24*325)+tan(24)-1294.43643*(1+2.1^(1.1+1.7))";
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
    char* string = "sum(pow(2*6,3^1.7),12834*127,1,2)";
    double result;
    if(decodeString(string) && decodeResult(&result)) {
        double expect = 11302639.1;
        printf("string: %s\r\nvalue: %f \r\nexpect: %f\n\n",string,result,expect);
    } else {
        printf("string: %s\r\nfailed",string);
    }
}

void test8() {
    char* string = "tanh(24*325)+sinh(24)-1294.43643*(1+2.1^(1.1+1.7))";
    double result;
    if(decodeString(string) && decodeResult(&result)) {
        double expect = -11629.1169;
        printf("string: %s\r\nvalue: %f \r\nexpect: %f\n\n",string,result,expect);
    } else {
        printf("string: %s\r\nfailed",string);
    }
}

void test9() {
    char* string = "log(10,12398)+ln(217834243) + sum(log(23,234),234)";
    double result;
    if(decodeString(string) && decodeResult(&result)) {
        double expect = 259.032457;
        printf("string: %s\r\nvalue: %f \r\nexpect: %f\n\n",string,result,expect);
    } else {
        printf("string: %s\r\nfailed",string);
    }
}

void test10() {
    char* string = "avg(log(10,12398)+ln(217834243) + SUM(log(23,234),234),2148,pow(214,3.435))*13.435+ Pow(sin(45),0.33) + 213%44 - 1.23*4.5^1.1 * log10(100000)*ln(12989)^5.111 + tan(55) + VARP(43245,2242893,log(1.1,32435)) - 992385*10.554";
//    char* string = "123*4.5^1.1 * log10(100000)*ln(12989)^5.111";
    double result;
    if(decodeString(string) && decodeResult(&result)) {
        double expect = 452999853.968539 + 0.891928519 + 213 - 44*4 - 6.433375141128 * 5 * 97849.8638811993  + 3290130732058.994/3 - 992385*10.554;
//        double expect =  643.3375141128 * 5 * 97849.8638811993;
        printf("string: %s\r\nvalue: %f \r\nexpect: %f\n\n",string,result,expect);
    } else {
        printf("string: %s\r\nfailed",string);
    }
    // 516727102661.6684 + 2192800249325.9958000000  + 580603380071.33 = 3290130732058.994
    // 20230734  9.47185812  97849.8638811993
}


int main(int argc, char *argv[]) {
//    test1();
//    test2();
//    test3();
//    test4();
//    test5();
//    test6();
//    test7();
//    test8();
//    test9();
    test10();
}
