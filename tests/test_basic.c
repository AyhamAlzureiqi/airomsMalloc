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
    int *c = airomsMalloc(sizeof(int));

    *a = 42;
    *b = 100;
    *c = 7;

     printf("before free:\n");
     heap_print();

     airomsFree(b);

     printf("after freeing b:\n");
     heap_print();

     airomsFree(a);

     printf("after freeing a (should coalesce with b):\n");
     heap_print();

     printf("a = %d\n", *a);
     printf("b = %d\n", *b);
     printf("a lives at: %p\n", (void *)a);
     printf("b lives at: %p\n", (void *)b);
     printf("gap: %ld bytes\n", (char *)b - (char *)a);

     heap_print();

return 0;
}
