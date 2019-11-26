#include "headerFiles.h"
extern void *base;

t_block fusion(t_block b){
	if (b->next && b->next->free ){
		b->size += BLOCK_SIZE + b->next->size;
		b->next = b->next->next;
		if (b->next) b->next->prev = b;
	}
	return (b);
}

t_block get_block(void *p){
	char *tmp;
	tmp = p;
	return (p = tmp -= BLOCK_SIZE);
}

// Valid addr for free
int valid_addr (void *p)
{
	if (base)
	{
		if (p>base && p<sbrk(0))
		{
			return (p == (get_block(p))->ptr);
		}
	}
	return (0);
}

void free(void *p){
	t_block b;
	if (valid_addr(p)){
		b = get_block(p);
		b->free = 1;
		/* fusion with previous if possible */
		if(b->prev && b->prev->free)
			b = fusion (b->prev);
		/* then fusion with next */
		if (b->next)
			fusion (b);
		else{
			/* free the end of the heap */
			if (b->prev) b->prev ->next = NULL;
			else
				/* No more block !*/
				base = NULL;
			brk(b);
		}
	}
}