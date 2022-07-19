/**
 * \file
 * \author Centrix14
 * \date 19.07.2022
 * \brief This file provides an interface to the UTSF library*/

#ifndef __LETO_LIBRARY_UTSF_LIBRARY_LETO_UTSF_HEADER_FILE_INCLUDED__
#define __LETO_LIBRARY_UTSF_LIBRARY_LETO_UTSF_HEADER_FILE_INCLUDED__

/** \addtogroup leto_utsf
 * @{
 */

/// UTSF container
/**
 * The structure of a UTSF container is a UTSF building block that stores a
 * single value
 */

typedef struct {
	void *data; ///< Pointer to the data stored by the container
	unsigned int size; ///< The amount of data stored by the container

	char *name; ///< Container name
} leto_utsf_container;

/// Alias for external usage
typedef leto_utsf_container utsf_contaiter;

leto_utsf_container *leto_utsf_container_init(char *name);
void leto_utsf_container_deinit(leto_utsf_container *container);

void leto_utsf_container_clear(leto_utsf_container *container);

void leto_utsf_container_add_data(leto_utsf_container *container,
								  void *data,
								  unsigned int size);

leto_utsf_container *leto_utsf_container_clone(leto_utsf_container
											  *container);

/** @} */

#endif
