#include "malloc.h"
#include "stdio.h"

int main(){
	int *aux = malloc(4);
	for(int i = 0; i < 4; i++){
		aux[i] = 2;
	}
	for(int i = 0; i < 8; i++){
		printf("aux%d: %d\n", i, aux[i]);
	}
	printf("realloc---------\n");
	realloc(aux,8);
	for(int i = 0; i < 8; i++){
		aux[i] = 2;
	}
	for(int i = 0; i < 8; i++){
		printf("aux%d: %d\n", i, aux[i]);
	}
	free(aux);
	for(int i = 0; i < 8; i++){
		printf("aux%d: %c\n", i, aux[i]);
	}
	return 0;
}