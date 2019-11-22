#include "malloc.h"

void *my_malloc(int size){
	struct Block *bestFit = NULL;
	struct Block *trace = NULL;

	if(head == NULL){
		//Initialize head and tail structs
		head = sbrk(sizeof(struct Block));
		tail = head;
		head->occ = 1;
		head->size = size + sizeof(struct Block);
		head->prev = NULL;
		head->next = NULL;
		return sbrk(size);
	}else{
		//Find smallest free block that is large enough
		trace = head;
		while(trace != NULL){
			if(trace->occ == 0){
				if(trace->size >= size + sizeof(struct Block) && (bestFit == NULL || trace->size < bestFit->size)){
					bestFit = trace;
					if(bestFit->size == size + sizeof(struct Block)){
						//Perfect fit found, return it
						bestFit->occ = 1;
						return (char*)bestFit + sizeof(struct Block);
					} 
				}
			}
			trace = trace->next;
		}
		if(bestFit == NULL){
			//No blocks of appropriate size empty, add after tail and set new tail
			bestFit = sbrk(sizeof(struct Block));
			bestFit->occ = 1;
			bestFit->size = size + sizeof(struct Block);
			bestFit-> prev = tail;
			bestFit->next = NULL;
			tail->next = bestFit;
			tail = bestFit;
			return sbrk(size);
		}else if(bestFit->size > sizeof(struct Block)*2 + size){
			//Split block
			trace = (struct Block*)((char*)bestFit + (sizeof(struct Block) + size));
			trace->next = bestFit->next;
			trace->prev = bestFit;
			trace->next->prev = trace;
			trace->occ = 0;
			trace->size = (int)(bestFit->size - (sizeof(struct Block)+size));
			bestFit->occ = 1;
			bestFit->size = sizeof(struct Block) + size;
			bestFit->prev = bestFit->prev;
			bestFit->next = trace;
			return (char*)bestFit + sizeof(struct Block);
		}else{
			//Block is not large enough to be split
			bestFit->occ = 1;
			return (char*)bestFit + sizeof(struct Block);
		}
	}

}

void my_free(void *ptr){
	struct Block *free = ptr - sizeof(struct Block);
	free->occ = 0;
	if(free != tail){
		//Block is not the tail
		if(free != head && free->prev->occ == 0){
			//Block is not the head, coalesce with previous
			free->prev->next = free->next;
			free->next->prev = free->prev;
			free->prev->size += free->size;
			free = free->prev;
		}
		if(free->next->occ == 0){
			//Coalesce with next
			free->size += free->next->size;
			free->next = free->next->next;
			free->next->prev = free;
		}
	}else{
		//Block is the tail
		tail = free;
		if(free == head){
			//Block is the only remaining block
			head = tail = NULL;
			sbrk(-free->size);
			return;
		}else{
			//Shrink the heap, set new tail
			tail = free->prev;
			tail->next = NULL;
			sbrk(-free->size);
			if(tail->occ == 0){
				//Tail is unoccupied, call my_free on tail
				my_free((char*)tail + sizeof(struct Block));
			}
		}
	}
}


void dump_heap()
{
    struct Block *cur;
    printf("brk: %p\n", sbrk(0));
    printf("head->");
    for(cur = head; cur != NULL; cur = cur->next) {
        printf("[%d:%d:%d]->", cur->occ, (int)((char*)cur - (char*)head), cur->size);
        fflush(stdout);
        assert((char*)cur >= (char*)head && (char*)cur + cur->size <= (char*)sbrk(0)); // check that block is within bounds of the heap
        if(cur->next != NULL) {
            assert(cur->next->prev == cur); // if not last block, check that forward/backward links are consistent
            assert((char*)cur + cur->size == (char*)cur->next); // check that the block size is correctly set
        }
    }
    printf("NULL\n");
}