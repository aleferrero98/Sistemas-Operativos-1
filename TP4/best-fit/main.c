#include "malloc.h"
#include "stdio.h"

int main(){
	char *aux = malloc(4);
	for(int i = 0; i < 4; i++){
		aux[i] = 2;
	}
	for(int i = 0; i < 4; i++){
		printf("aux%d: %d\n", i, aux[i]);
	}
	printf("free----------------------\n");
	free(aux);
	for(int i = 0; i < 4; i++){
		printf("aux%d: %c\n", i, aux[i]);
	}

	return 0;
}