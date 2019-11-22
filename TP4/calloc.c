#include "calloc.h"
#include "malloc.h"

void * calloc ( size_t number , size_t size ){
	size_t *new;
	size_t s4 ,i;
	new = malloc ( number * size );
	if (new) {
		s4 = align4 ( number * size) << 2;
		for (i=0; i<s4 ; i++) new[i] = 0;
	}
	return (new );
}