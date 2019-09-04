#Archivo Makefile que simplifica la compilacion

rdproc-v2: rdproc-v2.o
		gcc $(CFLAGS) -o rdproc-v2 rdproc-v2.o

rdproc-v2.o: rdproc-v2.c
		gcc $(CFLAGS) -c rdproc-v2.c

.PHONY: clean
clean:
		rm -f *.o rdproc-v2