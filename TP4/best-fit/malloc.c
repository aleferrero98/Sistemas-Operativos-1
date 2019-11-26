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
				if(trace->size >= size + sizeof(struct mab) && (bestFit == NULL || trace->size < bestFit->size)){
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
	mabPtr aux = ptr-sizeof(struct mab);
	aux->allocated = 0;
	if(aux != tail){
		//si el bloque no es el ultimo
		if(aux != head && aux->prev->allocated == 0){
			//el bloque no es la cabeza, se une con el anterior
			aux->prev->next = aux->next;
			aux->next->prev = aux->prev;
			aux->prev->size += aux->size;
			aux = aux->prev;
		}
		if(aux->next->allocated == 0){
			//se une con el siguiente
			aux->size += aux->next->size;
			aux->next = aux->next->next;
			aux->next->prev = aux;
		}
	}else{
		//si el bloque es la cola
		tail = aux;
		if(aux == head){
			//si es el unico bloque que queda
			head = tail = NULL;
			sbrk(-aux->size);
			return;
		}else{
			//achicamos el heap, seteamos una nueva tail
			tail = aux->prev;
			tail->next = NULL;
			sbrk(-aux->size);
			if(tail->allocated == 0){
				//tail esta ocupada, hacemos free en la cola
				free((char*)tail + sizeof(struct mab));
			}
		}
	}
}