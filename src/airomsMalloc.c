#include "airomsMalloc.h"
#include <unistd.h>
#include <stdio.h>

static block_header_t *head = NULL;

void *airomsMalloc(size_t size) {

    //Fit search
    block_header_t *current = head;
    while(current != NULL){
	if (current->is_free == 1 && current->size >= size){
		size_t leftover = current->size - size - HEADER_SIZE;
		if (leftover > 0){
			block_header_t *new_block = (block_header_t *)((char *)(current + 1) + size);
			new_block->size = leftover;
			new_block->is_free = 1;
			new_block->next = current->next;
			new_block->prev = current;
			current->next = new_block;
			if (new_block->next != NULL){
				new_block->next->prev = new_block;}
			current->size = size;}
		current->is_free = 0;
		return (void *)(current + 1);
	}
    current = current->next;
 }

    block_header_t *block_address = sbrk(HEADER_SIZE + size);

    //checks if sbrk failed
    if (block_address == (void *)-1){
	return NULL;}

    //filling header fields
    block_address->size = size;
    block_address->is_free = 0;
    block_address->next = NULL;
    block_address->prev = NULL;

    //head pointer update
    if (head == NULL) {
    	head = block_address;
    } else {
	block_header_t *current = head;
	while(current->next != NULL) {
	   current = current->next;}

	current->next = block_address;
	block_address->prev = current;}

    //return payload pointer
    return (void *)(block_address + 1);
}

void airomsFree(void *ptr) {

    block_header_t *Block = (block_header_t *)ptr - 1;
    Block->is_free = 1;

    //coalesce with right neigbor
    if(Block->next != NULL && Block->next->is_free == 1){
	Block->size = Block->size +  HEADER_SIZE + Block->next->size;
	Block->next = Block->next->next;
    if(Block->next != NULL) Block->next->prev = Block;}

    //coalesce with left neighbor
    if(Block->prev != NULL && Block->prev->is_free == 1){
	Block->prev->size = Block->prev->size + HEADER_SIZE + Block->size;
	Block->prev->next = Block->next;
    if(Block->next != NULL) Block->next->prev = Block->prev;
}}

void heap_print() {
    block_header_t *current = head;
    int i = 0;
    printf("\n-- Heap State --\n");
    while (current != NULL) {
        printf("[Block %d] addr=%p  size=%-6zu  %s\n",
            i,
            (void *)(current + 1),
            current->size,
            current->is_free ? "FREE" : "USED");
        current = current->next;
        i++;
    }
    if (i == 0) printf("(empty)\n");
    printf("----------------\n\n");
}
