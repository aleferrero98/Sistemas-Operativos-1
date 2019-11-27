#include "headerFiles.h"
#include <stdio.h>

void *realloc1(void *p, size_t size){
	size_t s;
	t_block b, new;
	void *newp;

	printf("entrando a realloc\n");

	if(!p) return (malloc1(size));
	if(valid_addr(p)){
		s = align4(size);
		b = get_block(p);
		if (b->size >= s){
			if(b->size - s >= (BLOCK_SIZE + 4)) split_block(b,s);
		}else{
			/* Try fusion with next if possible */
			if (b->next && b->next->free && (b->size + BLOCK_SIZE + b->next->size) >= s){
				fusion(b);
				if(b->size - s >= (BLOCK_SIZE + 4)) split_block(b,s);
			}else{
				/* good old realloc with a new block */
				newp = malloc1(s);
				if(!newp)
					/* we ’re doomed ! */
					return (NULL);
				/* I assume this work ! */
				new = get_block(newp);
				/* Copy data */
				copy_block(b,new);
				/* free the old one */
				free1(p);
				return (newp);
			}
		}
		return (p);
	}
	return (NULL);
}

/* Copy data from block to block */
void copy_block(t_block src , t_block dst)
{
	int *sdata , *ddata ;
	size_t i;
	sdata = src->ptr;
	ddata = dst->ptr;
	for (i=0; i*4<src ->size && i*4<dst ->size; i++)
		ddata[i] = sdata[i];
}