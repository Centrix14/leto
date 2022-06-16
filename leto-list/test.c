#include <stdio.h>
#include <assert.h>

#include "leto-list.h"

void tester(char *name, void (*func)());
void test_init();
void test_iterator();
void test_foreach();
void test_get_node_by_index();
void test_insert_node();

int main() {
	tester("init", test_init);
	tester("iterator", test_iterator);
	tester("foreach", test_foreach);
	tester("get_node_by_index", test_get_node_by_index);
	tester("insert_node", test_insert_node);
	
	return 0;
}

void tester(char *name, void (*func)()) {
	(*func)();
	printf("*** %s test PASS\n", name);
}

void test_init() {
	List *lst = NULL;

	lst = leto_list_init_node(NULL, NULL);
	leto_list_deinit_node(lst);
}

void test_iterator_print(void *data) {
	puts((char*)data);
}

void test_iterator() {
	List *lst = NULL;

	lst = leto_list_init_node(NULL, "root");
	for (int i = 0; i < 10; i++)
		leto_list_expand_list(lst, "hey");

	leto_list_iterator(lst, NULL, test_iterator_print);
	leto_list_iterator(lst, leto_list_deinit_node, NULL);
}

void test_foreach() {
	List *lst = NULL;

	lst = leto_list_init_node(NULL, "root");
	for (int i = 0; i < 10; i++)
		leto_list_expand_list(lst, "hey");

	leto_list_foreach(lst, test_iterator_print);
	leto_list_iterator(lst, leto_list_deinit_node, NULL);
}

void test_get_node_by_index() {
	List *lst = NULL, *second_node = NULL, *node_with_index_1 = NULL;

	lst = leto_list_init_node(NULL, "one");
	second_node = leto_list_expand_list(lst, "two");
	leto_list_expand_list(lst, "three");

	node_with_index_1 = leto_list_get_by_index(lst, 1);
	assert(second_node == node_with_index_1);
}

void test_insert_node() {
	List *lst = NULL, *insertable_node = NULL, *node_with_index_4 = NULL;

	lst = leto_list_init_node(NULL, "root");
	for (int i = 0; i < 10; i++)
		leto_list_expand_list(lst, "hey");

	insertable_node = leto_list_init_node(NULL, "insertable");
	leto_list_insert_node(lst, insertable_node, 4);

	node_with_index_4 = leto_list_get_by_index(lst, 4);
	assert(insertable_node == node_with_index_4);
}
