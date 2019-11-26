#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <assert.h>
#include <sys/types.h>


struct mab {
    int allocated;    // si el bloque esta ocupado
    size_t size;             // tamaño del bloque (incluyendo header)
    struct mab *prev;   // puntero al bloque previo
    struct mab *next;   // puntero al bloque siguiente
};
typedef struct mab *mabPtr;

void *malloc(size_t size);
void free(void *ptr);

mabPtr head;
mabPtr tail;