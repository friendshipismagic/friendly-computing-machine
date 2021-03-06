#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "tests.h"

// define the bit width of the binary numbers that can be processed.
#define N 5

// string representing the name of the currently running program
char *program = NULL;

// check whether the charater is a '0' or a '1'
int is_binary(char a)
{
	return a == '1' || a == '0';
}

// perform a logical and of the binary numbers a and b
char and(char a, char b)
{
	assert(is_binary(a) && is_binary(b));
	if (a == '0' || b  == '0')
		return '0';
	else
		return '1';
}

// perform a logical or of the binary numbers a and b
char or(char a, char b)
{
	assert(is_binary(a) && is_binary(b));
	if (a == '1' || b  == '1')
		return '1';
	else
		return '0';
}

// perform a logical xor of the binary numbers a and b
char xor(char a, char b)
{
	assert(is_binary(a) && is_binary(b));
	if (a == b)
		return '0';
	else
		return '1';
}

// add two binary numbers, returning the sum (s) and carry (c)
void half_adder(char a, char b, char *s, char *c)
{
	// Here is the truth table
	//  +---+---+---+---+
	//  | a | b | s | c |
	//  |---+---+---+---|
	//  | 1 | 1 | 0 | 1 |
	//  | 1 | 0 | 1 | 0 |
	//  | 0 | 1 | 1 | 0 |
	//  | 0 | 0 | 0 | 0 |
	//  +---+---+---+---+
	// So s is a xor b
	// and c is a and b

	assert(is_binary(a) && is_binary(b));
	*s = xor(a, b);
	*c = and(a, b);
}

// add two binary numbers and an input carry, returning the sum (s) and
// carry (c)
void full_adder(char a, char b, char c_in, char *s, char *c)
{
	// Here is the truth table
	//  +---+---+---+---+---+---+---+
	//  | a | b | s1| c1| ci| s | co|
	//  |---+---+---+---+---+---+---|
	//  | 1 | 1 | 0 | 1 | 0 | 0 | 1 |
	//  | 1 | 0 | 1 | 0 | 0 | 1 | 0 |
	//  | 0 | 1 | 1 | 0 | 0 | 1 | 0 |
	//  | 0 | 0 | 0 | 0 | 0 | 0 | 0 |
	//  | 1 | 1 | 0 | 1 | 1 | 1 | 1 |
	//  | 1 | 0 | 1 | 0 | 1 | 0 | 1 |
	//  | 0 | 1 | 1 | 0 | 1 | 0 | 1 |
	//  | 0 | 0 | 0 | 0 | 1 | 1 | 0 |
	//  +---+---+---+---+---+---+---+
	//

	char c_ab, s_ab, c_abc;
	half_adder(a, b, &s_ab, &c_ab);

	half_adder(s_ab, c_in, s, &c_abc);
	*c = or(c_ab, c_abc);
}

// perform an addition of two unsigned N-bit binary numbers, represented as
// strings
void addition(char *a, char *b, char *s)
{
	// Alexandre
	// ---------
	// Addition in little endian mode
	// Use half_adder for bootstrap, then full_adder
	// for cary propogation

	char c_in, c_out;

	// Avoid flush by splitting bootstrap and forloop addition with full_adder
	assert(is_binary(a[0]) && is_binary(b[0]));
	half_adder(a[0], b[0], s, &c_in);

	for(unsigned int i=1; i<N; ++i) {
		assert(is_binary(a[i]) && is_binary(b[i]));
		full_adder(a[i], b[i], c_in, s+i, &c_out);
		c_in = c_out;
	}
}

// perform an addition of two signed N-bit binary numbers, represented as
// strings, and perform an overflow check.
void addition_signed(char *a, char *b, char *s)
{
	if (*a == '\0' || *b == '\0') return;
	assert(is_binary(*a) && is_binary(*b));

	// Step 1 is to complement a
	char a_out[N];
	for(int i = 0; i<N; i++)
		a_out[i] = xor(a[i], '1');

	// Step 2 is to complement b
	char b_out[N];
	for(int i = 0; i<N; i++)
		b_out[i] = xor(b[i], '1');

	// Step 3 is to sum both
	char c_out[N];
	addition(a_out, b_out, c_out);

	// And add one to the result
	addition(c_out, "10000", c_out);

	// Invert ones and zeroes
	for(int i = 0; i<N; i++)
		s[i] = xor(c_out[i], '1');

	// Check for overflow
	if((a[N-1] == '1' && b[N-1] == '1' && s[N-1] == '0')
			|| (a[N-1] == '0' && b[N-1] == '0' && s[N-1] == '1')) {
		// start chrome and go to bufferoverflow.com
		fprintf(stderr, "[!] Overflow detected! Stopping now...\n");
		fprintf(stderr, "[!] a=%.*s, b=%.*s, result was %.*s\n",
				N, a, N, b, N, s);
		exit(2);
	}
}

// perform a subtraction of two N-bit binary numbers A and B, represented as
// strings: S = A - B - 1
void subtraction_minus_one(char *a, char *b, char *s)
{
	// First step is to convert B to -B-1 using two's complement
	char b_out[N+1];
	for(int i = 0; i<N; i++)
		b_out[i] = xor(b[i], '1');

	// Next step is just to sum A and b_out
	addition(a, b_out, s);
}

// convert an input binary number represented as string to a fixed-width binary
// number of length N.
//
// in case the input string is not to long or is not a binary numnber, an error
// is signaled.
void to_binary(char *str, char *bin)
{
	unsigned int l = strlen(str);
	int error = 0;

	for(unsigned int i = 0; i < l; i++)
	{
		if (str[i] != '1' && str[i] != '0')
		{
			error = 1;
			break;
		}
	}

	if (l > N || error)
	{
		fprintf(stderr, "%s: invalid unsigned number: \"%s\"\n", program, str);
		exit(1);
	}

	memcpy(&bin[N - l], str, l);
}

// retrieve two input numbers from the command line arguments, perform an
// unsigned addition, and print the result.
int main(int argc, char **argv)
{
	// store name of currently running program
	program = argv[0];

	// check number of command line arguments, and signal an error.
	if (argc != 3)
	{
		fprintf(stderr, "%s: expecting two unsigned integer values as command line "
				"arguments.\n", program);
		return 2;
	}

	// get and initialize two input binary numbers
	char a[N + 1];
	char b[N + 1];
	memset(a, '0', N); a[N] = '\0';
	memset(b, '0', N); b[N] = '\0';
	to_binary(argv[1], &a[0]);
	to_binary(argv[2], &b[0]);

	// initialize the result binary number
	char c[N + 1];
	memset(c, '0', N); c[N] = '\0';

	// perform the addition
	addition(a, b, c);

	// TODO: call addition_signed and subtraction_minus_one

	// print result
	printf("a:   %s\n", a);
	printf("b: + %s\n", b);
	printf("c:   %s\n", c);

	// TODO: print results of addition_signed and subtraction_minus_one

	return 0;
}
