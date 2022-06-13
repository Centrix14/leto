/**
 * \file
 * \author Centrix14
 * \date 11.06.2022
 * \brief The main file of the leto-list library, which implements singly
 * linked lists and operations with them
 */

#include <stdio.h>
#include <stdlib.h>

#include "leto-list.h"

/**
 * \brief This function initializes the list item
 * \param[in] next Pointer to next list element
 * \param[in] data Pointer to new element data
 * \return Pointer to new element
 *
 * \note In case of an error (for example, if memory could not be allocated),
 * the function prints a message to the standard error stream (stderr), after
 * which it returns NULL
 */

leto_t_list *leto_list_init_node(leto_t_list *next, void *data) {
	leto_t_list *required_node = NULL;

	required_node = (leto_t_list*)malloc(sizeof(leto_t_list));
	if (!required_node) {
		fprintf(stderr, "leto-list: fail to allocate memory for node\n");

		return NULL;
	}

	required_node->next = next;
	required_node->data = data;

	return required_node;
}

/**
 * \brief The function of freeing previously allocated memory.
 * \param[in] deinitialized_node The element that should be released
 *
 * \warning Remember that passing pointers to memory that has not been allocated to
 * the function is dangerous and may cause the application to crash.
 */

void leto_list_deinit_node(leto_t_list *deinitialized_node) {
	if (deinitialized_node)
		free(deinitialized_node);
}

/**
 * \brief List extension function. Adds a new element to the end.
 * \param[in] parent_node The tail of the list to which a new element is added.
 * \param[in] data A pointer to the data assigned to the new element.
 * \return New tail of the list (new element)
 */

leto_t_list *leto_list_add_node(leto_t_list *parent_node, void *data) {
	leto_t_list *new_node = NULL;

	new_node = leto_list_init_node(NULL, data);
	parent_node->next = new_node;

	return new_node;
}

/**
 * \brief Returns the last item in the list
 * \param[in] list The list in which the search is performed
 * \return Pointer to the last item in the list
 */

leto_t_list *leto_list_get_last(leto_t_list *list) {
	leto_t_list *node = NULL;

	node = list;
	while (node->next)
		node = node->next;
	
	return node;
}

/**
 * \brief Expands the list by adding a new element to it
 * \param[in] list An expandable list (not necessarily its beginning)
 * \param[in] data Pointer to the data stored by the new element
 * \return Pointer to the created element
 *
 * \warning Remember that this function modifies the list, it is not pure
 */

leto_t_list *leto_list_expand_list(leto_t_list *list, void *data) {
	leto_t_list *last = NULL;

	last = leto_list_get_last(list);

	return leto_list_add_node(last, data);
}

/**
 * \brief Assigns new data to the element
 * \param[in] node The element to which the data is assigned
 * \param[in] data Data assigned to the element
 *
 * \note Using this function may seem redundant, but it is not. It should be
 * used wherever possible, because in the future, it is possible to expand this
 * functionality, overload it (for example, adding logging)
 */

void leto_list_set_data(leto_t_list *node, void *data) {
	if (data)
		node->data = data;
}

int main(void) {
	List *lst = NULL, *node = NULL, *next = NULL;

	lst = leto_list_init_node(NULL, NULL);

	for (int i = 0; i < 9; i++) {
		leto_list_expand_list(lst, NULL);
	}

	node = lst;
	while (node) {
		next = node->next;

		leto_list_deinit_node(node);

		node = next;
	}

	return 0;
}
