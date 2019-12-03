#include "headerFiles.h"
#include <stdio.h>
void *base = NULL;

void split_block(t_block b, size_t s)
{
	t_block new;
	new = (t_block)(b->data + s);
	new->size = b->size - s - BLOCK_SIZE ;
	new->next = b->next;
	new->prev = b;
	new->free = 1;
	new->ptr = new->data;
	b->size = s;
	b->next = new;
	if(new->next) new->next->prev = new;
}

t_block extend_heap(t_block last , size_t s)
{
	t_block b;
	b = sbrk(0);
	sbrk(BLOCK_SIZE + s);
	b->size = s;
	b->next = NULL;
	b->prev = last;
	b->ptr = b->data;
	if(last) last->next = b;
	b->free = 0;
	return (b);
}

void *malloc1(size_t size){
	t_block b,last;
	size_t s;
	s = align4(size);
	printf("entrando a malloc\n");
	if(base){
		/* First find a block */
		last = base;
		b = find_block(&last ,s);
		if(b){
			/* can we split */
			if ((b->size - s) >= (BLOCK_SIZE + 4))
				split_block(b,s);
				b->free = 0;
		}else{
			/* No fitting block , extend the heap */
			b = extend_heap(last ,s);
			if(!b){
				printf("ERROR EN malloc1");
				return (NULL);
			}
		}
	}else{
		/* first time */
		b = extend_heap(NULL ,s);
		if(!b){
			printf("ERROR EN malloc2");
			return (NULL);
		}
			
		base = b;
	}
	return (b->data);
}

t_block find_block(t_block *last , size_t size){
    t_block b=base;
    while (b && !(b->free && b->size >= size)) {
        *last = b;
        b = b->next;
    }
    return (b);
}