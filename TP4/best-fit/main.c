#include "malloc.h"
#include "stdio.h"

int main(){
	char *aux = my_malloc(4);
	for(int i = 0; i < 4; i++){
		aux[i] = 2;
	}
	for(int i = 0; i < 4; i++){
		printf("aux%d: %d\n", i, aux[i]);
	}

	return 0;
}