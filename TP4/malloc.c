#include "malloc.h"

void split_block ( t_block b, size_t s)
{
	t_block new;
	new = ( t_block )(b->data + s);
	new ->size = b->size - s - BLOCK_SIZE ;
	new ->next = b->next;
	new ->prev = b;
	new ->free = 1;
	new ->ptr = new ->data;
	b->size = s;
	b->next = new;
	if (new ->next) new ->next ->prev = new;
}

t_block extend_heap ( t_block last , size_t s)
{
	int sb;
	t_block b;
	b = sbrk (0);
	sb = (int) sbrk ( BLOCK_SIZE + s);
	if (sb < 0) return (NULL );
	b->size = s;
	b->next = NULL;
	b->prev = last;
	b->ptr = b->data;
	if (last) last ->next = b;
	b->free = 0;
	return (b);
}