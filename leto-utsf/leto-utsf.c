/**
 * \file
 * \author Centrix14
 * \date 19.07.2022
 * \brief This file provides an implementation of the UTSF features
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../leto-error/leto-error.h"
#include "leto-utsf.h"

/**
 * \defgroup leto_utsf [leto-utsf] Universal Transport and Store Form \
 * library
 * @{
 */

/**
 * \brief Initializes an empty container
 * \param[in] name Name of the new container
 * \return New empty container
 */

leto_utsf_container *leto_utsf_container_init(char *name) {
	leto_utsf_container *container = NULL;

	container = (leto_utsf_container*)malloc(sizeof(leto_utsf_container));
	if (!container)
		leto_error(LEC_FAIL_MEMORY_ALLOCATION);

	container->data = NULL;
	container->size = 0;

	container->name = (char*)malloc(strlen(name) + 1);
	if (!container->name)
		leto_error(LEC_FAIL_MEMORY_ALLOCATION);
	strcpy(container->name, name);

	return container;
}

/**
 * \brief Frees the memory allocated for the container
 * \param[in] container The container whose memory will be freed
 *
 * \warning This function can also try to free the memory allocated for
 * data if the pointer to them is not NULL, remember this!
 */

void leto_utsf_container_deinit(leto_utsf_container *container) {
	if (container->name)
		free(container->name);
	if (container->data)
		free(container->data);
}

/**
 * \brief Clears the container
 * \param[in, out] container Container to be cleaned
 *
 * \note We believe that containers should be immutable, so the library does
 * not provide functions to change the contents of containers. This function
 * can be used in one case: if you yourself freed the data memory and want
 * to use the leto_utsf_container_deinit function after that
 */

void leto_utsf_container_clear(leto_utsf_container *container) {
	container->data = NULL;
	container->size = 0;
}

/**
 * \brief This function adds data to the container
 * \param[in, out] container Container to add data to
 * \param[in] data Data to be added to the container
 * \param[in] size Data size in bytes
 *
 * \warning Remember that size is the amount of data in bytes. Therefore, if
 * you need to add an array of numbers, then its volume will be considered
 * as the product of the length of the array by the volume of one number
 * \warning Remember also that containers cannot be reused, therefore,
 * calling this function again for the same container will cause an error
 */

void leto_utsf_container_add_data(leto_utsf_container *container,
								  void *data,
								  unsigned int size) {
	if (container->data)
		leto_error(LEC_REUSE_ATTEMPT);

	container->data = malloc(size);
	if (!container->data)
		leto_error(LEC_FAIL_MEMORY_ALLOCATION);

	container->size = size;
	memcpy(container->data, data, size);
}

/**
 * \brief Allows you to clone a container (create an identical one to the
 * original one, the data is also cloned)
 * \param[in] container Source container
 * \return Clone of the original container
 */

leto_utsf_container *leto_utsf_container_clone(leto_utsf_container
											  *container) {
	leto_utsf_container *clone = NULL;

	clone = leto_utsf_container_init(container->name);
	leto_utsf_container_add_data(clone, container->data,
								 container->size);

	return clone;
}

/** @} */
