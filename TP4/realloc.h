#ifndef _REALLOC_H_
#define _REALLOC_H_
//define todo lo necesario

#include "malloc.h"

// Copy data from block to block
void copy_block ( t_block src , t_block dst);
void * realloc (void *p, size_t size);

#endif //_REALLOC_H_