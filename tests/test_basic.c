#include <stdio.h>
#include "../src/airomsMalloc.h"

int main() {

    //check current sizes 
    printf("size_t:         %zu bytes\n", sizeof(size_t));
    printf("int:            %zu bytes\n", sizeof(int));
    printf("pointer:        %zu bytes\n", sizeof(void *));
    printf("block_header_t: %zu bytes\n", sizeof(block_header_t));
    printf("gap will be:    %zu bytes\n", sizeof(block_header_t) + sizeof(int));

    char *a = airomsMalloc(100);
    char *b = airomsMalloc(10);


     printf("before free:\n");
     heap_print();

     airomsFree(a);

     printf("after freeing a:\n");
     heap_print();

     char *c = airomsMalloc(20);

     printf("after allocating 20 bytes (should split a block):\n");
     heap_print();



     return 0;
}
