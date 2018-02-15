#include <stdio.h>
#include "cal_decode.h"

int main(int argc, char *argv[]) {
    
    char* string = "123.001+238432+11*23+(21367-213*34)";
    decodeString(string);
}
