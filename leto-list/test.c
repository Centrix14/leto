/**
 * \file
 * \author Centrix14
 * \date 25.06.2022
 * \brief File contains tests for leto-list library
 */

#include <stdio.h>
#include <assert.h>

#include "leto-list.h"

/**
 * \defgroup tests Tests
 * \defgroup leto_list_tests leto-list library tests
 * \ingroup tests
 * @{
 */

void tester(char *name, void (*func)());
void test_init();
void test_iterator();
void test_foreach();
void test_get_node_by_index();
void test_insert_node();
void test_eject_node();

/// main test function
int main() {
	tester("init", test_init);
	tester("iterator", test_iterator);
	tester("foreach", test_foreach);
	tester("get_node_by_index", test_get_node_by_index);
	tester("insert_node", test_insert_node);
	tester("eject_node", test_eject_node);
	
	return 0;
}

/**
 * \brief Function to simplify testing
 * \param[in] name Test name
 * \param[in] func Test function
 * 
 * This function does only two things: it calls the test function, and then
 * prints on the screen that the test has passed. Inside the testing function,
 * assert should be used.
 */

void tester(char *name, void (*func)()) {
	(*func)();
	printf("*** %s test PASS\n", name);
}

/**
 * \brief This test checks the correctness of the list initialization and
 * deinitialization functions
 * 
 * This test has two features: (1) it may fail with an assert, (2) it may fail
 * with a segmentation fault. However, in most cases this test is successful.
 */

void test_init() {
	List *lst = NULL;

	lst = leto_list_init_node(NULL, NULL);
	assert(lst == NULL);
	leto_list_deinit_node(lst);
}

/**
 * \brief Auxiliary function for iterator test
 * \param[in] data Data to be printed
 * 
 * This function takes a generalized pointer to a string as input, and then,
 * brought to a pointer to a character, prints it.
 */

void test_iterator_print(void *data) {
	puts((char*)data);
}

/**
 * \brief Iterator Test
 *
 * Checks the correctness of the iterator. It may result in a segmentation
 * fault, but in most cases it is successful. In the course of work, it prints
 * "hey" sequentially.
 */

void test_iterator() {
	List *lst = NULL;

	lst = leto_list_init_node(NULL, "root");
	for (int i = 0; i < 10; i++)
		leto_list_expand_list(lst, "hey");

	leto_list_iterator(lst, NULL, test_iterator_print);
	leto_list_iterator(lst, leto_list_deinit_node, NULL);
}

/**
 * \brief Foreach function test
 * 
 * See the description of test_iterator
 */

void test_foreach() {
	List *lst = NULL;

	lst = leto_list_init_node(NULL, "root");
	for (int i = 0; i < 10; i++)
		leto_list_expand_list(lst, "hey");

	leto_list_foreach(lst, test_iterator_print);
	leto_list_iterator(lst, leto_list_deinit_node, NULL);
}

/**
 * \brief get_by_index function test
 * 
 * Checks the correctness of the get_by_index function. It may result in an
 * assert trigger.
 */

void test_get_node_by_index() {
	List *lst = NULL, *expectation = NULL, *reality = NULL;

	lst = leto_list_init_node(NULL, "one");
	expectation = leto_list_expand_list(lst, "two");
	leto_list_expand_list(lst, "three");

	reality = leto_list_get_by_index(lst, 1);
	assert(expectation == reality);

	leto_list_iterator(lst, leto_list_deinit_node, NULL);
}

/**
 * \brief insert_node fuction test
 *
 * Checks the correctness of the insert_node function. It may result in an
 * assert trigger.
 */

void test_insert_node() {
	List *lst = NULL, *expectation = NULL, *reality = NULL;

	lst = leto_list_init_node(NULL, "root");
	for (int i = 0; i < 10; i++)
		leto_list_expand_list(lst, "hey");

	expectation = leto_list_init_node(NULL, "insertable");
	leto_list_insert_node(lst, expectation, 4);

	reality = leto_list_get_by_index(lst, 4);
	assert(expectation == reality);

	leto_list_iterator(lst, leto_list_deinit_node, NULL);
}

/**
 * \brief eject_node function test
 *
 * Checks the correctness of the eject_node function. It may result in an assert
 * trigger.
 */

void test_eject_node() {
	List *lst = NULL, *expectation = NULL, *reality = NULL;

	lst = leto_list_init_node(NULL, "root");

	leto_list_expand_list(lst, "first");
	expectation = leto_list_expand_list(lst, "eject me");
	leto_list_expand_list(lst, "second");

	reality = leto_list_eject_node(lst, 2);
	assert(expectation == reality);

	leto_list_iterator(lst, leto_list_deinit_node, NULL);
}

/** @} */
