#include "malloc.h"
#include <stdio.h>

int main(void){
	int *aux = malloc1(4*sizeof(int));
	for(int i = 0; i < 4; i++){
		aux[i] = i*3;
	}
	for(int i = 0; i < 4; i++){
		printf("aux%d: %d\n", i, aux[i]);
	}
	printf("pre-free\n");
	free1(aux);
	printf("post-free\n");

	return 0;
}