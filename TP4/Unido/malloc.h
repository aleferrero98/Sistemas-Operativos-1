#ifndef _MALLOC_H_
#define _MALLOC_H_
//define todo lo necesario
#include <sys/types.h>
#include <unistd.h>

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


void * malloc ( size_t size );
t_block find_block ( t_block *last , size_t size );
void split_block ( t_block b, size_t s);
t_block extend_heap ( t_block last , size_t s);
t_block fusion ( t_block b);
t_block get_block (void *p);
int valid_addr (void *p);
void free(void *p);
void * calloc ( size_t number , size_t size );
void copy_block ( t_block src , t_block dst);
void * realloc (void *p, size_t size);

#endif //_MALLOC_H_