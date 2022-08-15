#include <stdio.h>
#include <assert.h>
#include <string.h>

#include "leto-utsf.h"
#include "../leto-test/leto-test.h"

void test_init();
void test_clear();
void test_add_data();
void test_clone();

void test_utsf_init();
void test_utsf_append();

int main(void) {
	leto_test("init", test_init);
	leto_test("clear", test_clear);
	leto_test("add_data", test_add_data);
	leto_test("clone", test_clone);

	leto_test("utsf-init", test_utsf_init);
	leto_test("utsf-append", test_utsf_append);
	
	return 0;
}

void test_init() {
	utsf_contaiter *container = NULL;

	container = leto_utsf_container_init("test container");
	leto_utsf_container_deinit(container);
}

void test_clear() {
	utsf_contaiter *container = NULL;
	char *useless_data = "useless";

	container = leto_utsf_container_init("test container");
	container->data = useless_data;
	leto_utsf_container_clear(container);

	assert(container->data == NULL);

	leto_utsf_container_deinit(container);
}

void test_add_data() {
	utsf_contaiter *container = NULL;
	char test_data[] = "this is test data";

	container = leto_utsf_container_init("test container");

	leto_utsf_container_add_data(container, test_data, 18);

	assert(!strcmp(container->data, test_data));

	leto_utsf_container_deinit(container);
}

void test_clone() {
	utsf_contaiter *container = NULL, *clone = NULL;
	char test_data[] = "this is test data";
	int assert_value = 0;

	container = leto_utsf_container_init("test container");

	leto_utsf_container_add_data(container, test_data, 18);
	clone = leto_utsf_container_clone(container);

	assert_value =
		(!strcmp(container->name, clone->name)) &&
		(!strcmp(container->data, clone->data)) &&
		(container->size == clone->size);
	assert(assert_value);

	leto_utsf_container_deinit(container);
	leto_utsf_container_deinit(clone);
}

void test_utsf_init() {
	utsf *form = NULL;

	form = leto_utsf_init();
	leto_utsf_deinit(form);
}

void test_utsf_append() {
	utsf *form = NULL;

	form = leto_utsf_init();

	for (int i = 0; i < 10; i++)
		leto_utsf_append(form, "test-container");
	
	leto_utsf_deinit(form);
}
