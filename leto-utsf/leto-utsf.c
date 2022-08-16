/**
 * \file
 * \author Centrix14
 * \date 19.07.2022
 * \brief This file provides an implementation of the UTSF features
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../leto-type/leto-type.h"
#include "../leto-error/leto-error.h"
#include "../leto-list/leto-list.h"
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
	free(container);
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
								  common data,
								  positive size) {
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

/**
 * \brief Creates new UTSF
 * \return new UTSF
 * \warning If memory cannot be allocated for the new UTSF, the
 * function raises an error and the program terminates.
 */

leto_utsf *leto_utsf_init() {
	leto_utsf *form = NULL;

	form = (leto_utsf*)malloc(sizeof(leto_utsf));
	if (!form)
		leto_error(LEC_FAIL_MEMORY_ALLOCATION);

	form->data = NULL;
	form->length = 0;

	return form;
}

static void leto_utsf_container_deinit_wrapper(void *container) {
	leto_utsf_container_deinit((leto_utsf_container*)container);
}

/**
 * \brief Frees up the memory allocated for the form
 * \param[in] form Exempt form
 * 
 * The memory allocated for the form is released as follows:
 * 1. UTSF containers are released, along with their names and data, if any
 * 2. The singly linked list in which the containers are stored is released
 * 3. The form is being released
 */

void leto_utsf_deinit(leto_utsf *form) {
	if (!form)
		leto_warning(LWC_NULL_AS_OPTIONAL_PARAMETER);
	if (!form->data)
		leto_warning(LWC_NULL_AS_OPTIONAL_DATA);

	leto_list_foreach(form->data, leto_utsf_container_deinit_wrapper);
	leto_list_iterator(form->data, leto_list_deinit_node, NULL);

	free(form);
}

/**
 * \brief Adds a new container to the form
 * \param[in] form The form to which the container is added
 * \param[in] name Name of the new container
 */

void leto_utsf_append(leto_utsf *form, char *name) {
	leto_utsf_container *container = NULL;

	container = leto_utsf_container_init(name);
	
	if (form->data)
		leto_list_expand_list(form->data, container);
	else
		form->data = leto_list_init_node(NULL, container);
}

/**
 * \brief Adds a new container to the form
 * \param[in] form The form itself
 * \param[in] name Name of the new container
 * \param[in] pos The position where the container will be inserted
 */

void leto_utsf_insert(leto_utsf *form, char *name, position pos) {
	leto_utsf_container *new_container = NULL;
	leto_t_list *insertable_node = NULL;

	new_container = leto_utsf_container_init(name);
	insertable_node = leto_list_init_node(NULL, new_container);

	leto_list_insert_node(form->data, insertable_node, pos);
}

/**
 * \brief Remove the container from the form
 * \param[in] form The form itself
 * \param[in] pos The position from which the container will be removed
 */

void leto_utsf_eject(leto_utsf *form, position pos) {
	leto_list_eject_node(form->data, pos);
}

/** @} */
