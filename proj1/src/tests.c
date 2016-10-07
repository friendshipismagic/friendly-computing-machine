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
    static n=1;
    printf("TEST N° %i : %s", n++, str);
}

int main() {

    test("half_adder 1 1");
    {
        char a = '1';
        char b = '1';
        char s = 0;
        char c = 0;
        half_adder(a,b,&s, &c);
        assert(s=='0' && c=='1');
        pass();
    }


    return 0;
}
