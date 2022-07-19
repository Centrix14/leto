/**
 * \file
 * \author Centrix14
 * \date 27.06.2022
 * \brief The file contains functions and macros for handling errors and
 * warnings
 */

#ifndef __LETO_LIBRARY_INTERNAL_ERROR_SYSTEM_LETO_ERROR_HEADER_FILE_INCLUDED__
#define __LETO_LIBRARY_INTERNAL_ERROR_SYSTEM_LETO_ERROR_HEADER_FILE_INCLUDED__

#include <stdlib.h>

/**
 * \defgroup leto-error Handling Errors and Warnings
 * @{
 */

/// Memory allocation error
/**
 * An error that occurs when there are problems with memory allocation
 */

#define LEC_FAIL_MEMORY_ALLOCATION "Fail to allocate memory"

/// Pass NULL error
/**
 * Error when passing NULL as a required parameter
 */

#define LEC_REQUIRED_PARAMETER_IS_NULL "Passed NULL as a mandatory parameter"

/// Error getting data
/**
 * Notifies that somewhere inside the function it was not possible to get data
 */

#define LEC_FAIL_TO_GET_REQUIRED_DATA "Fail to get required data"

/// Error opening a dynamic library
/**
 * This error occurs when a non-program fails to open a dynamic library
 */

#define LEC_FAIL_TO_OPEN_DYNAMIC_LIBRARY "Fail to open dynamic library"

/// Symbol import error
/**
 * This error occurs when the program fails to import the required symbol from
 * the dynamic library
 */

#define LEC_FAIL_TO_GET_REQUIRED_SYMBOL "Fail to get required symbol"

/// Error closing dynamic library
/**
 * This error occurs when the program cannot close the dynamic library correctly
 */

#define LEC_FAIL_TO_CLOSE_DYNAMIC_LIBRARY "Fail to close dynamic library"

/// Container reuse error
/**
 * This error occurs when trying to reuse the container, i.e. add data
 * even though it already exists
 */

#define LEC_REUSE_ATTEMPT "An attempt to reuse the container, add data" \
	"to it, although it already contains something, was stopped"

/// NULL Optional Parameter Warning
/**
 * This warning is triggered when NULL is passed to any function as an
 * optional parameter
 */

#define LWC_NULL_AS_OPTIONAL_PARAMETER "NULL passed as an optional parameter"

/// Abstraction over leto_error_handle
/**
 * Handles an error, outputs information about the file, function and line in
 * which the error occurred to the error stream, takes the error message as an
 * argument
 */

#define leto_error(error_msg) \
	leto_error_handle(error_msg, __FILE__, (char*)__func__, __LINE__)

/// Abstraction over leto_warning_handle
/**
 * Processes warnings, prints information about the file, function and line to
 * the console, takes the text of the warning as a parameter
 */

#define leto_warning(warning_msg) \
	leto_warning_handle(warning_msg, __FILE__, (char*)__func__, __LINE__)

/**
 * \brief Handles errors
 * \param[in] error_msg Error message
 * \param[in] file The name of the file in which the error occurred
 * \param[in] func The name of the function in which the error occurred
 * \param[in] line The line number where the error occurred
 *
 * \warning This is a noreturn function, after which the program ends
 */

_Noreturn void leto_error_handle(char *error_msg, char *file, char *func, int line) {
	fprintf(stderr, "ERROR in %s:%s line %d: %s\n", file, func, line, error_msg);
	exit(EXIT_FAILURE);
}

/**
 * \brief Handles warnings
 * \param[in] warning_msg Warning message
 * \param[in] file The name of the file in which the warning occurred
 * \param[in] func The name of the function which the warning occurred
 * \param[in] line The line number where the warning occerred
 */

void leto_warning_handle(char *warning_msg, char *file, char *func, int line) {
	fprintf(stderr, "WARNING in %s:%s line %d: %s\n", file, func, line, warning_msg);
}

#endif

/** @} */
