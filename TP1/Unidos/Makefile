#Archivo Makefile que simplifica la compilacion

rdproc: main.o
		gcc $(CFLAGS) -o rdproc main.o

main.o: main.c
		gcc $(CFLAGS) -c stepA.h stepB.h stepC.h main.c

.PHONY: clean
clean:
		rm -f *.o rdproc
		rm -f *.gch