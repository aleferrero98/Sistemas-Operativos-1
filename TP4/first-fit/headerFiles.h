#ifndef _HEADERFILES_H_
#define _HEADERFILES_H_
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
	char data[1];
};
typedef struct s_block *t_block ;


// Define the block size since the sizeof will be wrong
#define BLOCK_SIZE 20

// Split block according to size.
// The b block must exist .
void split_block(t_block b, size_t s);

// Add a new block at the of heap
// return NULL if things go wrong
t_block extend_heap(t_block last , size_t s);
void *malloc1(size_t size);

// Copy data from block to block
void copy_block(t_block src , t_block dst);
void *realloc1(void *p, size_t size);

void free1(void *p);
t_block get_block(void *p);
int valid_addr(void *p);
t_block fusion(t_block b);

void *calloc1(size_t number , size_t size);

t_block find_block(t_block *last , size_t size);

#define align4(x) (((((x)-1)>>2)<<2)+4)

#endif //_HEADERFILES_H_