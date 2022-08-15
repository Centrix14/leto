/**
 * \file
 * \author Centrix14
 * \date 10.06.2022
 * \brief Header file of the library of singly linked lists leto-list
 */

#ifndef __LETO_LIBRARY_LIST_SYSTEM_LETO_LIST_HEADER_FILE_INCLUDED__
#define __LETO_LIBRARY_LIST_SYSTEM_LETO_LIST_HEADER_FILE_INCLUDED__

/**
 * \defgroup leto_list [leto-list] Library for working with singly linked \
 * lists
 * @{
 */

/// Type of element processing function
/**
 * A macro is a type of function that processes a list item. Is taken as an argument
 * by the iterator.
 */

#define LETO_T_IFUNC_NODE(name) void (*name)(leto_t_list*)

/// Type of element data processing function
/**
 * A macro is a type of function that processes the data of a list item. Is
 * taken as an argument by the iterator.
 */

#define LETO_T_IFUNC_DATA(name) void (*name)(void*)

/// Structure of a singly linked list element
/**
 * This structure implements an element of a singly linked list. These lists can
 * be used not only inside the library, but also outside it. Be careful when
 * working with this structure, remember that it stores a general type pointer
 * to your data.
 */

struct __leto_list_list_t__ {
	struct __leto_list_list_t__ *next; ///< Pointer to the next element
	void *data; ///< Pointer to the data stored by the element
};

/// typedef for __leto_list_list_t__
/**
 * The leto_t_list type (abbreviation for __leto_list_list_t___)
 * is intended for use inside the library.
 */

typedef struct __leto_list_list_t__ leto_t_list;

/// typdef for __leto_list_list_t__
/**
 * List (abbreviation for __leto_list_list_t__) is intended for use outside the
 * library, can be replaced by leto_t_list.
 */

typedef struct __leto_list_list_t__ List;

leto_t_list *leto_list_init_node(leto_t_list *next, void *data);
void leto_list_deinit_node(leto_t_list *deinitialized_node);
leto_t_list *leto_list_add_node(leto_t_list *parent_node, void *data);
leto_t_list *leto_list_get_last(leto_t_list *list);
leto_t_list *leto_list_expand_list(leto_t_list *list, void *data);
void leto_list_set_data(leto_t_list *node, void *data);
void leto_list_iterator(leto_t_list *list,
						LETO_T_IFUNC_NODE(node_func),
						LETO_T_IFUNC_DATA(data_func));
void leto_list_foreach(leto_t_list *list, LETO_T_IFUNC_DATA(data_func));
leto_t_list *leto_list_get_by_index(leto_t_list *list, unsigned int pos);
void leto_list_insert_node(leto_t_list *list, leto_t_list *node, unsigned int pos);
leto_t_list *leto_list_eject_node(leto_t_list *list, unsigned int pos);

/** @} */

#endif
