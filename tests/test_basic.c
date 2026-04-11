#include <stdio.h>
#include "../src/airomsMalloc.h"

int main() {

    //check current sizes 
    printf("size_t:         %zu bytes\n", sizeof(size_t));
    printf("int:            %zu bytes\n", sizeof(int));
    printf("pointer:        %zu bytes\n", sizeof(void *));
    printf("block_header_t: %zu bytes\n", sizeof(block_header_t));
    printf("gap will be:    %zu bytes\n", sizeof(block_header_t) + sizeof(int));

    int *a = airomsMalloc(sizeof(int));
    int *b = airomsMalloc(sizeof(int));


    *a = 42;
    *b = 100;


     printf("before free:\n");
     heap_print();

     airomsFree(a);

     printf("after freeing a:\n");
     heap_print();

     int *c = airomsMalloc(sizeof(int));
     *c = 99;

     printf("after allocating c (should reuse a block):\n");
     heap_print();





     printf("a lives at: %p\n", (void *)a);
     printf("c lives at: %p\n", (void *)c);



return 0;
}
