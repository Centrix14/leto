#ifndef __LETO_LIBRARY_UTSF_LIBRARY_LETO_UTSF_HEADER_FILE_INCLUDED__
#define __LETO_LIBRARY_UTSF_LIBRARY_LETO_UTSF_HEADER_FILE_INCLUDED__

typedef struct {
	void *data;
	unsigned int size;

	char *name;
} leto_utsf_container;

typedef leto_utsf_container utsf_contaiter;

leto_utsf_container *leto_utsf_container_init(char *name);
void leto_utsf_container_deinit(leto_utsf_container *container);

void leto_utsf_container_clear(leto_utsf_container *container);

void leto_utsf_container_add_data(leto_utsf_container *container,
								  void *data,
								  unsigned int size);

leto_utsf_container *leto_utsf_container_clone(leto_utsf_container
											  *container);

#endif
