/**
 * \file
 * \author Centrix14
 * \date 30.06.2022
 * \brief 
 */

#include <stdio.h>
#include <assert.h>

#include "../leto-test/leto-test.h"
#include "leto-so.h"

/**
 * \defgroup leto_so_tests leto-so library tests
 * \ingroup tests
 * @{
 */

void test_get_symbol();

int main() {
	leto_test("get_symbol", test_get_symbol);
	
	return 0;
}

/**
 * \brief Leto-so library test
 *
 * This test checks the operation of 3 functions at once: loading dynamic
 * libraries, getting symbols from them and closing libraries.
 */

void test_get_symbol() {
	int (*multiple_func)(int, int) = NULL;
	int multiple_func_result = 0;
	void *test_library = NULL;

	test_library = leto_so_open_library("/home/user/leto/leto-so/test-library.so");
	multiple_func = (int (*)(int, int))leto_so_get_symbol(test_library, "multiple");

	multiple_func_result = multiple_func(2, 3);

	leto_so_close_library(test_library);
	assert(multiple_func_result == 6);
}

/** @} */
