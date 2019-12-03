#include "headerFiles.h"
#include <stdio.h>

void *calloc1(size_t number , size_t size){
	size_t *new;
	size_t s4 ,i;

	printf("entrando a calloc\n");
	new = malloc1(number * size);
	if(new){
		s4 = align4(number*size)<<2;
		for(i=0; i<s4 ; i++) new[i] = 0;
	}
	return (new);
}