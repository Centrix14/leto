/**
 * \file
 * \author Centrix14
 * \date 13.09.2022
 * \brief leto-test library realization
 */

#include "leto-test.h"

/**
 * \addtogroup leto_test
 * @{
 */

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
