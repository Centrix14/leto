/**
 * \file
 * \author Centrix14
 * \date 10.06.2022
 * \brief Header file of the library of singly linked lists leto-list
 */

#ifndef __LETO_LIBRARY_LIST_SYSTEM_LETO_LIST_HEADER_FILE_INCLUDED__
#define __LETO_LIBRARY_LIST_SYSTEM_LETO_LIST_HEADER_FILE_INCLUDED__

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
 * List (abbreviation for __leto_list_list_t__)is intended for use outside the
 * library, can be replaced by leto_t_list.
 */

typedef struct __leto_list_list_t__ List;

#endif
