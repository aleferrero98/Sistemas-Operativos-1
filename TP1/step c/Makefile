#Archivo Makefile que simplifica la compilacion

rdproc-v3: rdproc-v3.o
		gcc $(CFLAGS) -o rdproc-v3 rdproc-v3.o

rdproc-v3.o: rdproc-v3.c
		gcc $(CFLAGS) -c rdproc-v3.c

.PHONY: clean
clean:
		rm -f *.o rdproc-v3