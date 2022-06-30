/**
 * \file
 * \author Centrix14
 * \date 30.06.2022
 * \brief This file provides basic functionality for unit-testing
 */

#ifndef __LETO_LIBRARY_TEST_SYSTEM_LETO_TEST_HEADER_FILE_INCLUDED__
#define __LETO_LIBRARY_TEST_SYSTEM_LETO_TEST_HEADER_FILE_INCLUDED__

/**
 * \defgroup leto_test Simple unit testing system
 * @{
 */

void leto_test(char *name, void (*func)());

/**
 * \brief The function of conducting a simple test
 * \param[in] name test name
 * \param[in] func test funcion
 *
 * \warning Remember that the test function must use assert for verification
 *
 * This function provides a simple interface for testing. If the test function
 * returns control (test passed successfully) then the corresponding message is
 * displayed on the screen
 */

void leto_test(char* name, void (*func)()) {
	(*func)();
	printf("*** %s test PASS\n", name);
}

/** @} */

#endif
