#ifndef __LETO_LIBRARY_TEST_SYSTEM_LETO_TEST_HEADER_FILE_INCLUDED__
#define __LETO_LIBRARY_TEST_SYSTEM_LETO_TEST_HEADER_FILE_INCLUDED__

void leto_test(char *name, void (*func)());

void leto_test(char* name, void (*func)()) {
	(*func)();
	printf("*** %s test PASS\n", name);
}

#endif
