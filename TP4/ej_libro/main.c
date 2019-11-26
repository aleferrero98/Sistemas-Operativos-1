#include "headerFiles.h"
#include <stdio.h>

int main(void){
	printf("sizeof: %lu\n", sizeof(int));
	int *aux, *aux2;
	aux = (int *)malloc(4*sizeof(int));
	//printf("aux: %d\n", *aux);
	for(int i = 0; i < 4; i++){
		aux[i]=i;
		printf("aux%d: %d\n", i, aux[i]);
	}
	//free(aux);
	/*
	for(int i = 1; i <= 4; i++){
		aux[i] = 2;
	}/*
	for(int i = 0; i < 8; i++){
		printf("aux%d: %d\n", i, aux[i]);
	}*/
	printf("----------realloc---------\n");
	realloc(aux,8*sizeof(int));
	for(int i = 0; i < 8; i++){
		aux[i] = 2;
	}
	for(int i = 0; i < 8; i++){
		printf("aux%d: %d\n", i, aux[i]);
	}
	free(aux);
	printf("----------calloc---------\n");
	aux2=calloc(4 , sizeof(int));
	for(int i = 0; i < 4; i++){
		printf("aux2-%d: %d\n", i, aux2[i]);
	}
	free(aux2);
	/*
	for(int i = 0; i < 8; i++){
		printf("aux%d: %d\n", i, aux[i]);
	}*/
	return 0;
}