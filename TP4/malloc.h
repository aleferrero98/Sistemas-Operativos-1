#ifndef _MALLOC_H_
#define _MALLOC_H_
//define todo lo necesario
#include <sys/types.h>
#include <unistd.h>
// block struct
struct s_block {
	size_t size;
	struct s_block *next;
	struct s_block *prev;
	int free;
	void *ptr;
	/* A pointer to the allocated block */
	char data [1];
};
typedef struct s_block *t_block ;


// Define the block size since the sizeof will be wrong
#define BLOCK_SIZE 20

// Split block according to size.
// The b block must exist .
void split_block ( t_block b, size_t s);

// Add a new block at the of heap
// return NULL if things go wrong
t_block extend_heap ( t_block last , size_t s);

#endif //_MALLOC_H_