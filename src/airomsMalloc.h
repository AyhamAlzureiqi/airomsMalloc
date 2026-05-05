#ifndef AIROMS_MALLOC_H
#define AIROMS_MALLOC_H
#define ALIGN(size) (((size) + 7) & ~7)

#include <stddef.h>

typedef struct block_header {
	size_t size;
	int is_free;
	struct block_header *next;
	struct block_header *prev;
} block_header_t;



#define HEADER_SIZE sizeof(block_header_t)

void *airomsMalloc(size_t size);
void airomsFree(void *ptr);
void heap_print();

#endif
