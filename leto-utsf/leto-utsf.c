/**
 * \file
 * \author Centrix14
 * \date 19.07.2022
 * \brief This file provides an implementation of the UTSF features
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>

#include "leto-utsf.h"

/**
 * \defgroup leto_utsf [leto-utsf] Universal Transport and Store Form \
 *  library
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
 * \return Returns the extracted list item
 */

leto_t_list *leto_utsf_eject(leto_utsf *form, position pos) {
	return leto_list_eject_node(form->data, pos);
}

/**
 * \brief Creates a new form based on the existing one. 
 * \param[in] form Original form
 * \return New form
 * This function provides one of three methods for creating new forms.
 * The construction involves creating a new form with the same fields as 
 * the original one. The data is not copied during the construction.
 */

leto_utsf *leto_utsf_construct(leto_utsf *form) {
	leto_utsf *constructed_form = NULL;
	leto_t_list *form_content = NULL;
	leto_utsf_container *form_container = NULL;

	constructed_form = leto_utsf_init();
	form_content = form->data;
	while (form_content) {
		form_container = (leto_utsf_container*)form_content->data;
		leto_utsf_append(constructed_form, form_container->name);
		
		form_content = form_content->next;
	}

	return constructed_form;
}

/**
 * \brief Cloning the form
 * \param[in] form Original form
 * \return New form
 * This function provides a second method of creating new forms — cloning. 
 * When cloning, the new form will have the same fields and data as the 
 * original one.
 */

leto_utsf *leto_utsf_clone(leto_utsf *form) {
	leto_utsf *cloned_form = NULL;
	leto_t_list *form_content = NULL;
	leto_utsf_container *form_container = NULL, *cloned_container = NULL;

	cloned_form = leto_utsf_init();
	form_content = form->data;
	while (form_content) {
		form_container = form_content->data;
		cloned_container = leto_utsf_container_clone(form_container);
		
		if (cloned_form->data)
			leto_list_expand_list(cloned_form->data, cloned_container);
		else
			cloned_form->data = leto_list_init_node(NULL, cloned_container);

		form_content = form_content->next;
	}

	return cloned_form;
}

/**
 * \brief The function of filling in the form field
 * \param[in,out] form The form whose field will be filled in
 * \param[in] field_name Name of the field to be filled in
 * \param[in] size Data volume
 * \param[in] data Data to be entered in the field
 */

void leto_utsf_fill_field(leto_utsf *form, char *field_name,
						  positive size, void *data) {
	leto_t_list *form_content = NULL;
	leto_utsf_container *container = NULL;

	form_content = form->data;
	while (form_content) {
		container = (leto_utsf_container*)form_content->data;
		if (!strcmp(container->name, field_name))
			leto_utsf_container_add_data(container, data, size);

		form_content = form_content->next;
	}
}

/**
 * \brief Function for filling in multiple fields
 * \param[in,out] form The form whose fields will be filled in
 * This function takes a variable number of arguments equal to 1 + 3×n, 
 * where 1 is form, and n is the number of fields to fill in.
 *
 * The general view of the function call is as follows:
 * \code{.c}
 * leto_utsf_apply(form,
 *                 field_name_1, field_size_1, field_data_1,
 *                 field_name_2, field_size_2, field_data_2
 *                 ...);
 * \endcode
 * Also, specifically for the convenience of programming, two macros have 
 * been introduced: _p and _v. They can be used to shorten the code as 
 * follows:
 * \code{.c}
 * leto_utsf_apply(form,
 *                 field_name_1, _v(field_data_1),
 *                 field_name_2, _v(field_data_2)
 *                 ...);
 * \endcode
 * Read about the use of these macros in the relevant section of the 
 * documentation
 */

void leto_utsf_apply(leto_utsf *form, ...) {
	va_list args_list;
	char *field_name = NULL;
	positive size = 0;
	common data = NULL;

	va_start(args_list, form);

	field_name = va_arg(args_list, char*);
	size = va_arg(args_list, positive);
	data = va_arg(args_list, common);
	while (field_name && size && data) {
		leto_utsf_fill_field(form, field_name, size, data);
		
		field_name = va_arg(args_list, char*);
		size = va_arg(args_list, positive);
		data = va_arg(args_list, common);
	}
	
	va_end(args_list);
}

/** @} */
