/**
 * \file
 * \author Centrix14
 * \date 15.08.2022
 * \brief leto-error library realization
 */

#include <stdio.h>
#include <stdlib.h>

#include "../leto-type/leto-type.h"

/**
 * \addtogroup leto-error
 * @{
 */

/**
 * \brief Handles errors
 * \param[in] error_msg Error message
 * \param[in] file The name of the file in which the error occurred
 * \param[in] func The name of the function in which the error occurred
 * \param[in] line The line number where the error occurred
 *
 * \warning This is a noreturn function, after which the program ends
 */

_Noreturn void leto_error_handle(char *error_msg,
								 char *file,
								 char *func,
								 positive line) {
	fprintf(stderr, "ERROR in %s:%s line %d: %s\n",
			file, func, line, error_msg);
	exit(EXIT_FAILURE);
}

/**
 * \brief Handles warnings
 * \param[in] warning_msg Warning message
 * \param[in] file The name of the file in which the warning occurred
 * \param[in] func The name of the function which the warning occurred
 * \param[in] line The line number where the warning occerred
 */

void leto_warning_handle(char *warning_msg,
						 char *file,
						 char *func,
						 positive line) {
	fprintf(stderr, "WARNING in %s:%s line %d: %s\n",
			file, func, line, warning_msg);
}

/** @} */
