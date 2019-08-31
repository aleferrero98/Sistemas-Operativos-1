#Archivo Makefile que simplifica la compilacion

rdproc-v1: rdproc-v1.o
		gcc $(CFLAGS) -o rdproc-v1 rdproc-v1.o

rdproc-v1.o: rdproc-v1.c
		gcc $(CFLAGS) -c rdproc-v1.c

.PHONY: clean
clean:
		rm -f *.o rdproc-v1