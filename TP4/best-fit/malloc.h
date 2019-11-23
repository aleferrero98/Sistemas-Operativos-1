#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <assert.h>
#include <sys/types.h>


struct mab {
    int allocated;    // whether block is occupied
    size_t size;             // size of block (including header)
    struct Block *prev;   // pointer to previous block
    struct Block *next;   // pointer to next block
};
typedef struct mab *mabPtr;

void *malloc(size_t size);
void free(void *ptr);

mabPtr head;
mabPtr tail;