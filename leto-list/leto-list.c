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

int main(void) {
	List *lst = NULL, *node = NULL, *next = NULL;

	lst = leto_list_init_node(NULL, NULL);
	node = leto_list_add_node(lst, NULL);

	for (int i = 0; i < 9; i++) {
		node = leto_list_add_node(node, NULL);
		printf("%d\n", i);
	}

	node = lst;
	for (int i = 0; i < 11; i++) {
		next = node->next;

		leto_list_deinit_node(node);
		node = next;

		printf("%d\n", i);
	}
	
	return 0;
}
