#Archivo Makefile que simplifica la compilacion

rdproc-v4: rdproc-v4.o
		gcc $(CFLAGS) -o rdproc-v4 rdproc-v4.o

rdproc-v4.o: rdproc-v4.c
		gcc $(CFLAGS) -c rdproc-v4.c

.PHONY: clean
clean:
		rm -f *.o rdproc-v4