/**
 * \file
 * \author Centrix14
 * \date 19.07.2022
 * \brief This file provides an interface to the UTSF library
 */

#ifndef __LETO_LIBRARY_UTSF_LIBRARY_LETO_UTSF_HEADER_FILE_INCLUDED__
#define __LETO_LIBRARY_UTSF_LIBRARY_LETO_UTSF_HEADER_FILE_INCLUDED__

#include "../leto-type/leto-type.h"
#include "../leto-error/leto-error.h"
#include "../leto-list/leto-list.h"

/** \addtogroup leto_utsf
 * @{
 */

/// Macro typifier for pointers
/**
 * A special macro for shortening the call record of the 
 * leto_utsf_fill_field and leto_utsf_apply functions. It is designed to be 
 * used together with pointers. The macro is expanded into two arguments: 
 * size and data.
 *
 * In the case when a string is passed to him, he, using strlen(), 
 * determines its length and outputs size equal to strlen(str) + 1.
 *
 * In other cases, the size is determined via sizeof.
 */
#define _p(data) _Generic((data),						\
						  char*: strlen(data) + 1,		\
						  default: sizeof(data)), data

/// Macro typifier for values
/**
 * A special macro for shortening the call record of the 
 * leto_utsf_fill_field and leto_utsf_apply functions. It is designed to be 
 * used together with the values. The macro is expanded into two arguments: 
 * size and data.
 *
 * The size is determined via sizeof.
 */

#define _v(data) sizeof(data), &data

/// UTSF container
/**
 * the structure of a UTSF container is a UTSF building block that stores a
 * single value
 */

typedef struct {
	void *data; ///< Pointer to the data stored by the container
	unsigned int size; ///< The amount of data stored by the container

	char *name; ///< Container name
} leto_utsf_container;

/// UTSF (Universal Transport and Store Form)
/**
 * UTSF is a special data type designed to store and transmit a variety
 * of different types of data. UTSF is based on a UTSF container and a
 * singly linked list. You can read more about UTSF in the corresponding
 * section of the documentation.
 */

typedef struct {
	leto_t_list *data; ///< Pointer to the list of containers
	unsigned int length; ///< List length
} leto_utsf;

/// Alias for external usage
typedef leto_utsf_container utsf_contaiter;

/// Alias for external usage
typedef leto_utsf utsf;

leto_utsf_container *leto_utsf_container_init(char *name);
void leto_utsf_container_deinit(leto_utsf_container *container);

void leto_utsf_container_clear(leto_utsf_container *container);

void leto_utsf_container_add_data(leto_utsf_container *container,
								  void *data,
								  unsigned int size);

leto_utsf_container *leto_utsf_container_clone(leto_utsf_container
											  *container);

leto_utsf *leto_utsf_init();
void leto_utsf_deinit(leto_utsf *form);
void leto_utsf_append(leto_utsf *form, char *name);
void leto_utsf_insert(leto_utsf *form, char *name, unsigned int pos);
leto_t_list *leto_utsf_eject(leto_utsf *form, position pos);

leto_utsf *leto_utsf_construct(leto_utsf *form);

void leto_utsf_fill_field(leto_utsf *form, char *field_name,
						  positive size, void *data);
void leto_utsf_apply(leto_utsf *form, ...);

/** @} */

#endif
