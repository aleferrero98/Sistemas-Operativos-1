#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <assert.h>

struct Block {
    unsigned char occ;    // whether block is occupied
    int size;             // size of block (including header)
    struct Block *prev;   // pointer to previous block
    struct Block *next;   // pointer to next block
};

void *my_malloc(int size);
void my_free(void *ptr);
void dump_heap();

struct Block *head;
struct Block *tail;