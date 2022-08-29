/**
 * \file
 * \author Centrix14
 * \date 30.06.2022
 * \brief leto-so library header file
 */

#ifndef __LETO_LIBRARY_SHARED_OBJECTS_SYSTEM_LETO_SO_HEADER_FILE_INCLUDED__
#define __LETO_LIBRARY_SHARED_OBJECTS_SYSTEM_LETO_SO_HEADER_FILE_INCLUDED__

#include "../leto-type/leto-type.h"
#include "../leto-error/leto-error.h"

/**
 * \addtogroup leto_so
 * @{
 */

void *leto_so_open_library(char *library_name);
void *leto_so_get_symbol(common library, char *symbol_name);
void leto_so_close_library(common library);

/** @} */

#endif
