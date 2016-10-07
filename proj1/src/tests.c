#define main main_temp1
#include "addition.c"
#undef main
#define main main_temp2
#undef main

#include <stdio.h>

int is_fail = 0;

void pass() {
    printf("\t\t\t\t[OK]\n");
}

void fail() {
    printf("\t\t\t\t[FAIL]\n");
    is_fail = 1;
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
    fflush(stdout);
    half_adder(a,b, &_s, &_c);
    assert(s==_s && c==_c);
    pass();
}

void full_adder_test(char a, char b, char c_in, char s, char c) {
    char _s = 0, _c = 0;
    char msg[40];
    sprintf(msg, "full_adder a:%c b:%c c_in:%c", a, b, c_in);
    test(msg);
    fflush(stdout);
    full_adder(a,b,c_in, &_s, &_c);
    int error = s==_s && c==_c;
    if (!error)  fail();
    else         pass();
}

int main() {
    half_adder_test('0','0','0','0');
    half_adder_test('0','1','1','0');
    half_adder_test('1','0','1','0');
    half_adder_test('1','1','0','1');

    full_adder_test('0','0','0','0','0');
    full_adder_test('1','0','0','1','0');
    full_adder_test('0','1','0','1','0');
    full_adder_test('0','0','1','1','0');
    full_adder_test('1','1','0','0','1');
    full_adder_test('1','0','1','0','1');
    full_adder_test('0','1','1','0','1');
    full_adder_test('1','1','1','1','1');

    return -is_fail;
}
