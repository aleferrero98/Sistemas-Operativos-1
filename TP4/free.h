#ifndef _FREE_H_
#define _FREE_H_
//define todo lo necesario

#include "malloc.h"

void free(void *p);
t_block get_block (void *p);
int valid_addr (void *p);
t_block fusion ( t_block b);

#endif //_FREE_H_