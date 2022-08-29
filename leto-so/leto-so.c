/**
 * \file
 * \author Centrix14
 * \date 30.06.2022
 * \brief Library for safe work with dynamic libraries
 */

#include <stdio.h>
#include <dlfcn.h>

#include "leto-so.h"

/**
 * \defgroup leto_so [leto-so] Working with dynamic libraries
 * @{
 */

/**
 * \brief The function of safe loading of dynamic libraries
 * \param[in] library_name Name of the library to download
 * \return Returns a pointer to an open library
 * \note Remember that it is better to specify the full path in the downloaded
 * library, even if it is located in the loader directory (dlfcn features)
 */

void *leto_so_open_library(char *library_name) {
	void *dynamic_library = NULL;

	dynamic_library = dlopen(library_name, RTLD_LAZY);
	if (!dynamic_library)
		leto_error(LEC_FAIL_TO_OPEN_DYNAMIC_LIBRARY);
	return dynamic_library;
}

/**
 * \brief The function of safely importing symbols from the library
 * \param[in] library A pointer to the library from which the symbol is loaded
 * \param[in] symbol_name Name of the imported symbol (variable or function)
 * \return Pointer to the imported character
 */

void *leto_so_get_symbol(common library, char *symbol_name) {
	void *required_symbol = NULL;

	required_symbol = dlsym(library, symbol_name);
	if (!required_symbol)
		leto_error(LEC_FAIL_TO_GET_REQUIRED_SYMBOL);
	return required_symbol;
}

/**
 * \brief Library safe unloading function
 * \param[in] library Unloaded library
 */

void leto_so_close_library(common library) {
	int is_close_error = 0;

	is_close_error = dlclose(library);
	if (is_close_error)
		leto_error(LEC_FAIL_TO_CLOSE_DYNAMIC_LIBRARY);
}

/** @} */
