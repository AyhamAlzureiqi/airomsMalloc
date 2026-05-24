#AiromsMalloc - Memory Allocator in C

airomsMalloc is a system level memory allocator built entirely on C,
with Free(), Coalescing, and Memory alignment.


##FEATURES:

  - Block splitting: Splits a block into two separate blocks if a single block is larger than requested
  - Memory Alignment: Makes the allocator more memory efficient by rounding up the requested block size to a multiple of 8 Bytes
  - Coalescing: Merges adjacent free blocks into a larger free block



##Building

`gcc -Wall src/airomsMalloc.c tests/test_basic.c -o test_basic`


##Usage

`./test_basic`


##Technical details

The allocator work in the system memory level, it can manipulate regions of memory
whether its making them grow using sbrk(), which is how the allocator requests memory from the OS,
splitting, or creating completely new regions of memory.



##Design

   - block_header_t * is a pointer for the current block and other blocks, it allows the allocator to know what the size of the current block is
     check whether its free to use or not, allows it to assign a next and previous blocks, for functions like coalescing
   - The heap: [ header ][ payload ][ header ][payload] ...
     The heap is the region where dynamic memory lives. 
   - Coalescing: Solves the problem of having fragementation with free blocks, it instead merges adjacent blocks into one block so large
                 allocations can reuse that space. it looks for two adjacent free blocks using if statements and merges them together 
   - Block splitting: Fixes the problem of giving the user more Bytes than requested. It splits by creating a 
                      new memory block that is the leftover of the original block


##Testing
`valgrind --leak-check=full ./test_basic`
Passes with 0 errors and 0 memory leaks


##Project Structure

`airomsMalloc/
 |---src/
 |   |---airomsMalloc.c  # Main program code
 |   |---airomsMalloc.h
 |---tests
 |   |---test_basic.c    # Commands to run and test the allocator
 |---README.md


##Learning Outcomes

This project demonstrates the understanding of:
Learned and Understood How memory works in the system level
More Expertise Systems programming in C
Algorithm design
Debugging and testing discipline using Valgrind, the program passes with 0 errors
Data structures applied to a real problem of improperly allocated memory


##Author

Ayham ALZureiqi Computer Engineering student @German Jordanian University


