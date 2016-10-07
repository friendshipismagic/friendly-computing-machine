#define main main_temp1
#include "addition.c"
#undef main
#define main main_temp2
#undef main

#include <stdio.h>

void pass() {
    printf("\t\t[OK]\n");
}

void test(char* str) {
    static int n=1;
    printf("TEST N° %i : %s", n++, str);
}

void half_adder_test(char a, char b, char s, char c) {
    char _s = 0, _c = 0;
    char msg[40];
    sprintf(msg, "half_adder %c %c", a, b);
    test(msg);
    half_adder(a,b, &_s, &_c);
    assert(s==_s && c==_c);
    pass();
}

int main() {
    half_adder_test('0','0','0','0');
    half_adder_test('0','1','1','0');
    half_adder_test('1','0','1','0');
    half_adder_test('1','1','0','1');


    return 0;
}
