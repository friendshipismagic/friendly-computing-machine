#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <stdint.h>
#include <inttypes.h>

// string representing the name of the currently running program
char *program = NULL;

// perform an unsigned multiplication of two unsigned numbers
uint64_t multiplication(uint32_t a, uint32_t b)
{
	if (a == 0 || b == 0) return 0;
	if (a == 1) return b;
	if (b == 1) return a;

	uint64_t out = a;
	for (uint32_t i = 0; i < b - 1; i++)
		out += a;
	return out;
}

// convert a number represented as string to an unsigned integer.
//
// in case the string is not a number or represents a too small/large number,
// an error is signaled.
uint32_t to_uint32(char *str)
{
	char *endptr = NULL;
	long int a = strtol(str, &endptr, 10);

	if (*endptr != '\0' || a < 0 || errno == ERANGE)
	{
		fprintf(stderr, "%s: invalid unsigned number: \"%s\"\n", program, str);
		exit(1);
	}

	return a;
}

// retrieve two input numbers from the command line arguments, perform an
// unsigned multiplication, and print the result.
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

	// get two input numbers
	uint32_t a = to_uint32(argv[1]);
	uint32_t b = to_uint32(argv[2]);

	// perform multiplication
	int64_t c = multiplication(a, b);

	// print result
	printf("%" PRIu32 " * %" PRIu32 " = %" PRIu64 "\n", a, b, c);

	return 0;
}
