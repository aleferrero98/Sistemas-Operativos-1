#include "malloc.h"

void *malloc(size_t size){
	mabPtr bestFit = NULL;
	mabPtr trace = NULL;

	if(head == NULL){
		//inicializamos head y tail
		head = sbrk(sizeof(struct mab));
		tail = head;
		head->allocated = 1;
		head->size = size + sizeof(struct mab);
		head->prev = NULL;
		head->next = NULL;
		return sbrk(size);
	}
	else{
		//encontrar el bloque mas pequeño lo suficientemente grande
		trace = head;
		while(trace != NULL){
			if(trace->allocated == 0){
				if(trace->size >= size + sizeof(struct Block) && (bestFit == NULL || trace->size < bestFit->size)){
					bestFit = trace;
					if(bestFit->size == size + sizeof(struct mab)){
						//encontramos el tamano perfecto
						bestFit->allocated = 1;
						return (char *) bestFit + sizeof(struct mab);
					}
				}
			}
			trace = trace->next;
		}
		if(bestFit == NULL){
			//si no hubo un bloque del tamano exacto vacio, lo agregamos despues de la tail y seteamos nueva tail
			bestFit = sbrk(sizeof(struct mab));
			bestFit->allocated = 1;
			bestFit->size = size + sizeof(struct mab);
			bestFit->prev = tail;
			bestFit->next = NULL;
			tail->next = bestFit;
			tail = bestFit;
			return sbrk(size);
		}
		else if(bestFit->size > sizeof(struct mab)*2 + size){
			//dividimos el bloque
			trace = (mabPtr)((char *)bestFit + (sizeof(struct mab) + size));
			trace->next = bestFit->next;
			trace->prev = bestFit;
			trace->next->prev = trace;
			trace->allocated = 0;
			trace->size = (size_t)(bestFit->size - (sizeof(struct mab) + size));
			bestFit->allocated  = 1;
			bestFit->size = sizeof(struct mab) + size;
			bestFit->prev = bestFit->prev;
			bestFit->next = trace;
			return (char*)bestFit + sizeof(struct mab);
		}
		else{
			//el bloque no es lo suficientemente largo para dividirlo
			bestFit->allocated = 1;
			return (char*)bestFit + sizeof(struct mab);
		}
	}	
}

void free(void *ptr){
	mabPtr free = ptr-sizeof(struct mab);
	free->allocated = 0;
	if(free != tail){
		//si el bloque no es el ultimo
		if(free != head && free->prev->allocated == 0){
			//el bloque no es la cabeza, se une con el anterior
			free->prev->next = free->next;
			free->next->prev = free->prev;
			free->prev->size += free->size;
			free = free->prev;
		}
		if(free->next->allocated == 0){
			//se une con el siguiente
			free->size += free->next->size;
			free->next = free->next->next;
			free->next->prev = free;
		}
	}else{
		//si el bloque es la cola
		tail = free;
		if(free == head){
			//si es el unico bloque que queda
			head = tail = NULL;
			sbrk(-free->size);
			return;
		}else{
			//achicamos el heap, seteamos una nueva tail
			tail = free->prev;
			tail->next = NULL;
			sbrk(-free->size);
			if(tail->allocated == 0){
				//tail esta ocupada, hacemos free en la cola
				free((char*)tail + sizeof(struct mab));
			}
		}
	}
}