#ifndef __TESTS_H__
#define __TESTS_H__

#ifdef exit
#undef exit
#endif

#define exit exit_test

int _has_exit = 0;

void exit_test(int x) {
	_has_exit = 1;
}

int has_exited() {
	int x = _has_exit;
	_has_exit = 0;
	return x;
}

#ifdef fprintf
#undef fprintf
#endif

#define fprintf no_fprintf

int no_fprintf(FILE* stream, const char* format, ...){

	return 0;
}

#endif




