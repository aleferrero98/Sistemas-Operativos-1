#include "headerFiles.h"
#include <stdio.h>

int main(void){
	printf("sizeof: %lu\n", sizeof(int));
	int *aux, *aux2;
	aux = (int *)malloc1(4*sizeof(int));

	for(int i = 0; i < 4; i++){
		aux[i]=i;
	}
	for(int i = 0; i < 4; i++){
		printf("aux%d: %d\n", i, aux[i]);
	}
	//free(aux);
	
	printf("----------realloc---------\n");
	realloc1(aux,8*sizeof(int));
	for(int i = 0; i < 8; i++){
		aux[i] = 2;
	}
	for(int i = 0; i < 8; i++){
		printf("aux%d: %d\n", i, aux[i]);
	}
	free1(aux);
	printf("----------calloc---------\n");
	aux2=calloc1(4 , sizeof(int));
	for(int i = 0; i < 4; i++){
		printf("aux2-%d: %d\n", i, aux2[i]);
	}
	free1(aux2);
	return 0;
}