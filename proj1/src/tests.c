#define main main_temp1
#include "addition.c"
#undef main
#define main main_temp2
#undef main

#include <stdio.h>
#include <math.h>

int is_fail = 0;
int _buffer_size = 0;
const int _margin = 80;

void pad() {
    for(int i=_buffer_size; i<= _margin; ++i) putchar(' ');
    _buffer_size = 0;
}

void pass() {
    pad();
    printf("[OK]\n");
}

void fail() {
    pad();
    printf("[FAIL]\n");
    is_fail += 1;
}

void test(char* str) {
    static int n=1;
    printf("TEST N° %i : %s", n++, str);
    _buffer_size += strlen(str) + 11 + (int) log10(n-1);
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
    fflush(stdout);
    full_adder(a,b,c_in, &_s, &_c);
    sprintf(msg, "full_adder a:%c b:%c c_in:%c, got _s:%c _c:%c", a, b, c_in, _s, _c);
    test(msg);
    int correct = s==_s && c==_c;
    if (!correct)  fail();
    else         pass();
}

void addition_test(char a[], char b[], char s[]) {
    char _s [N+1]; _s[0] = '\0';_s[N]= '\0';
    char msg[80];
    addition(a, b, _s);
    sprintf(msg, "addition a:%s b:%s s:%s, got _s:%s", a, b, s, _s);
    test(msg);
    int correct = strcmp(_s, s) == 0;
    if (!correct)  fail();
    else           pass();
}

void addition_signed_test(char a[], char b[], char s[]) {
    char _s[N+1]; _s[0] = '\0'; _s[N]= '\0';
    char msg[80];
    addition_signed(a,b,_s);
    sprintf(msg, "addition signed a:%s b:%s s:%s, got _s:%s", a, b, s, _s);
    test(msg);
    int correct = strcmp(_s,s) == 0;
    if (!correct) fail();
    else          pass();
}

void addition_signed_overflow_test(char a[], char b[], int overflow) {
    char _s[N+1]; _s[0] = '\0'; _s[N]= '\0';
    char msg[80];
    addition_signed(a,b,_s);
    int ov = has_exited();
    sprintf(msg, "addition signed a:%s b:%s, overflow:%s, got:%s", a, b, overflow?"yes":"no", ov? "yes":"no");
    test(msg);
    int correct = ov && overflow;
    if (!correct) fail();
    else          pass();
}

void subtraction_minus_one_test(char a[], char b[], char s[]) {
    char _s[N+1]; _s[0] = '\0'; _s[N]= '\0';
    char msg[80];
    subtraction_minus_one(a,b,_s);
    sprintf(msg, "subtraction_minus_one signed a:%s b:%s s:%s, got _s:%s", a, b, s, _s);
    test(msg);
    int correct = strcmp(_s,s) == 0;
    if (!correct) fail();
    else          pass();
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

    addition_test("10000", "10000", "01000"); // carry check
    addition_test("00010", "00001", "00011"); // addition check
    addition_test("11110", "11110", "01111"); // both
    addition_test("10101", "11100", "00111"); // random
    addition_test("11111", "10000", "00000");

    addition_signed_test("00000", "00000", "00000"); // stupid error check
    addition_signed_test("11111", "10000", "00000"); // -1 + 1 = 0, endian check
    addition_signed_test("10000", "10000", "01000"); //  1 + 1 = 2, basic adder
    addition_signed_test("11111", "10000", "00000"); //  1 + 2 = 3, basic adder
    addition_signed_test("00000", "11111", "11111"); //  0 - 1 = -1, zero test
    addition_signed_test("11111", "11111", "01111"); // -1 - 1 = -2, two negative
    addition_signed_test("11111", "10000", "00000"); // -1 - 2 = -3, with carry
    addition_signed_test("00001", "00001", "00000"); // overflow test
    // TODO: overflow are tested in addition.tests makefile 
    
    subtraction_minus_one_test("10000", "10000", "11111");
    subtraction_minus_one_test("10000", "00000", "00000");
    subtraction_minus_one_test("00000", "11111", "00000");
    subtraction_minus_one_test("11111", "11100", "11101");

    return -is_fail;
}
