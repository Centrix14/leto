#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../leto-error/leto-error.h"
#include "leto-utsf.h"

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

void leto_utsf_container_deinit(leto_utsf_container *container) {
	if (container->name)
		free(container->name);
	if (container->data)
		free(container->data);
}

void leto_utsf_container_clear(leto_utsf_container *container) {
	container->data = NULL;
	container->size = 0;
}

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

leto_utsf_container *leto_utsf_container_clone(leto_utsf_container
											  *container) {
	leto_utsf_container *clone = NULL;

	clone = leto_utsf_container_init(container->name);
	leto_utsf_container_add_data(clone, container->data,
								 container->size);

	return clone;
}
